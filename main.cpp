#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>
#include <sstream> 
#include <string>
using namespace std;


struct Image 
{
	bool horizontal; 
	vector<string> tags;
	int numTags; 

	void Print()
	{
		if (horizontal) 
			cout << "H ";
		else 
			cout << "V ";

		cout << numTags << " ";
		for (int i = 0; i < tags.size(); i++)
		{
			cout << tags[i] << " ";
		}
		cout << endl;
	}
	
};



int getScore(Image left, Image right)
{
	int common = 0;

	for (unsigned int i = 0; i < left.tags.size(); i++)
	{
		for (unsigned int j = 0; j < right.tags.size(); j++)
		{
			if (left.tags[i] == right.tags[j])
				common++;
		}
	}

	int leftCount = left.tags.size() - common;
	int rightCount = right.tags.size() - common;

	int returner1 = min(common, leftCount);
	int returner2 = min(returner1, rightCount);

	return returner2;
}

struct Slide
{
	vector<string> slideTags;
	int numTags;
	bool horizontal;
	bool used;

	Slide slideCreationV(Image one, Image two)
	{
		Slide combo;
		combo.slideTags = one.tags;
		for (unsigned int i = 0; i < two.numTags; i++)
		{
			combo.slideTags.push_back(two.tags[i]);
		}
	}

	Slide slideCreationH(Image one)
	{
		Slide horiz;
		horiz.slideTags = one.tags;
		horiz.numTags =
	}
};

struct Collection
{
	vector<Image> images;  //horizontal
	vector<Image> vertImage;  // verticals 
	int numPhotos;
	string line, temp, temp2; 
	Image tempImage; 

	Collection(){}

	Collection(string inputFile)
	{
		fstream file(inputFile);
		getline(file, line);
		
		numPhotos = atoi(line.c_str());

		for (int i = 0; i < numPhotos; i++)
		{
			getline(file, line);

			stringstream ss(line); 
			
			getline(ss, temp, ' '); 
			tempImage.horizontal = temp == "H" ? true : false;
			getline(ss, temp2, ' ');
			tempImage.numTags = stoi(temp2);
			for (int i = 0; i < tempImage.numTags; i++)
			{
				string tempTag;
				
				if (i != tempImage.numTags - 1)
					getline(ss, tempTag, ' ');
				else 
					getline(ss, tempTag);
				
				tempImage.tags.push_back(tempTag);
			}
			if (tempImage.horizontal)
				images.push_back(tempImage);
			else
				vertImage.push_back(tempImage);

			tempImage.tags.clear();
		}	
		
		// This works
		// for (int i = 0; i < images.size(); i++)
		// {
		// 	images[i].Print();
		// }
		
	}


};

vector<Slide> getSlides(vector<Image> vertImage)
{
	unsigned int loopsize = vertImage.size() / 2;
	vector<Slide> returnVect;
	for (unsigned int i = 0; i < loopsize; i++)
	{
		Slide newSlide;
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 2)
		cout << "Enter more than 2 input line arguments" << endl;
	else 
	{
		Collection collection(argv[1]);
		// collection->sortThem();
		
		// cout << getScore(collection.images[0], collection.images[1]) << endl;

		
		
	}		 

	return 0;
}
