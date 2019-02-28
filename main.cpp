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
	int id; 

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
	vector<Image> images; 
	int numTags;
	bool horizontal;
	bool used;

	Slide()
	{
		this->numTags = 0;
		this->horizontal = true;
		this->used = false;
	}

	Slide(Image one, Image two)
	{
		images.push_back(one);
		images.push_back(two);
		this->slideTags = one.tags;
		for (unsigned int i = 0; i < two.numTags; i++)
		{
			bool add;
			for (unsigned int j = 0; j < this->slideTags.size(); j++)
			{
				if (this->slideTags[j] == two.tags[i])
					add = false;
			}

			if (add)
				this->slideTags.push_back(two.tags[i]);
		}
		this->horizontal = false; // these are vertical
		this->used = false;
		this->numTags = this->slideTags.size();
	}

	Slide(Image one)
	{
		images.push_back(one);
		this->slideTags = one.tags;
		this->used = false;
		this->horizontal = true;
		this->numTags = one.tags.size();
	}

	void Print()
	{
		for (int i = 0; i < images.size(); i++)
		{
			if (i != images.size() - 1)
			{
				cout << images[i].id << " ";
			}
			else
				cout << images[i].id << endl;
		}
	}

};

struct Collection
{
	vector<Image> images;  //horizontal
	vector<Image> vertImage;  // verticals 
	int numPhotos;
	string line, temp, temp2; 
	Image tempImage; 
	int counter = 0;

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
			tempImage.id = counter++; 
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

vector<Slide> getSlides(vector<Image> horizontals, vector<Image> verticals)
{
	vector<Slide> ret;


	for (int i = 0; i < horizontals.size(); i++)
	{
		Slide temp(horizontals[i]); 
		ret.push_back(temp);
	}
	for (int i = 0; i < verticals.size(); i+=2)
	{
		Slide temp(verticals[i], verticals[i+1]);
		ret.push_back(temp);
	}

	return ret;

}

int main(int argc, char const *argv[])
{
	if (argc < 2)
		cout << "Enter more than 2 input line arguments" << endl;
	else 
	{
		{
			Collection collection(argv[1]);
			// collection->sortThem();

			// cout << getScore(collection.images[0], collection.images[1]) << endl;

			vector<Slide> output = getSlides(collection.images, collection.vertImage);

			cout << output.size() << endl;
			for (int i = 0; i < output.size(); i++)
			{
				output[i].Print();
			}
		}
		{
			
		}
		

	}		 

	return 0;
}
