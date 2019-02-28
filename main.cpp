#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>
#include <sstream> 
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

struct Collection
{
	vector<Image> images; 
	int numPhotos;
	string line, temp, temp2; 
	Image tempImage; 

	Collection(){}

	Collection(string inputFile)
	{
		fstream file(inputFile);
		getline(file, line);
		
		// num photos 
		numPhotos = atoi(line.c_str());
		// loop through all photos 

		for (int i = 0; i < numPhotos; i++)
		{
			getline(file, line);

			stringstream ss(line); 
			

			getline(ss, temp, ' '); 
			// cout << temp << endl;
			tempImage.horizontal = temp == "h" ? true : false;
			getline(ss, temp2, ' ');
			// cout << temp2 << endl;
			tempImage.numTags = stoi(temp2);
			for (int i = 0; i < tempImage.numTags; i++)
			{
				string tempTag;
				
				if (i == tempImage.numTags - 1)
				{
					getline(ss, tempTag, ' ');
				}
				else 
				{
					getline(ss, tempTag);
				}
				
				tempImage.tags.push_back(tempTag);
			}

			images.push_back(tempImage);
			tempImage.tags.clear();

			

		}	
		
		// This works
		// for (int i = 0; i < images.size(); i++)
		// {
		// 	images[i].Print();
		// }

		
	}

};



int main(int argc, char const *argv[])
{
	if (argc < 2)
		cout << "Enter more than 2 input line arguments" << endl;
	else 
	{
		Collection *collection = new Collection(argv[1]);
		// collection->GetInput(argv[1]);
	}		 

	return 0;
}
