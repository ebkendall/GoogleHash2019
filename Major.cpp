#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
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

    Collection() {}

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
            tempImage.horizontal = temp == "h" ? true : false;
            getline(ss, temp2, ' ');
            tempImage.numTags = stoi(temp2);
            for (int i = 0; i < tempImage.numTags; i++)
            {
                string tempTag;

                if (i == tempImage.numTags - 1)
                    getline(ss, tempTag, ' ');
                else
                    getline(ss, tempTag);

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