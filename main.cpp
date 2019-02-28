#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>
#include <sstream> 
#include <string>
#include <map> 
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
	map<string, int> freq;

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

				freq[tempTag]++;
				
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

struct less_than_key
{
	inline bool operator()(const Image &struct1, const Image &struct2)
	{
		return (struct1.numTags < struct2.numTags);
	}
};

struct less_than_key2
{
	inline bool operator()(const Slide &struct1, const Slide &struct2)
	{
		return (struct1.numTags < struct2.numTags);
	}
};


vector<Slide> getSlides(vector<Image> horizontals, vector<Image> verticals)
{
	vector<Slide> ret;
	int verticalsSize = verticals.size();
	int j = 0;

	sort(horizontals.begin(), horizontals.end(), less_than_key());
	sort(verticals.begin(), verticals.end(), less_than_key());

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

	sort(ret.begin(), ret.end(), less_than_key2());

	return ret;

}

map<string, vector<Slide>> getSlides2(map<string, int> freq, vector<Slide> output)
{
	map<string, vector<Slide>> ret;
	vector<Slide> temp;
	for (auto it = freq.begin(); it != freq.end(); it++)
	{
		for (int i = 0; i < output.size(); i++)
		{
			for (int j = 0; j < output[i].slideTags.size(); j++)
			{
				if (it->first == output[i].slideTags[j])
				{
					temp.push_back(output[i]);
				}
			}
			ret[it->first] = temp;
			temp.clear();
		}
	}
	return ret;
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

		vector<Slide> output = getSlides(collection.images, collection.vertImage);

		cout << output.size() << endl;
		for (int i = 0; i < output.size(); i++)
		{
			output[i].Print();
		}

		// map<string, vector<Slide>> allSlides = getSlides2(collection.freq, output);
	


	}		 

	return 0;
}
