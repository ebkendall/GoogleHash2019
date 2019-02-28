/*
photos
arrange into a slideshows that is as interesting as possible
Photo: either ONE Horizontal or TWO vertical sidebyside
Tag groups cannot have any overlap in tags
You cannot have a photo more than once

SCORE:
    interesting transitions
    the transitions need a theme based on the tags
    Two photos can have tags in common
    High Score

Steps:
    You dont have to use all of the photos provided, but you cannot
    use one photo more than once
    Choose order of photos such that the transition score is optimized
    Soring is based soly on the tags provided
    Taking the minimum of the three scores
        Need a function to calculate each of the three different scores
    Now, in terms of actual three functions
        1. number of common tags between the two
        2. number of tags in S1, not in S2
        3. number of tags in S2, not in S1


*/

int NumberFunction(Image one, Image two)
{
    int common = 0;
    for (unsigned int i = 0; i < one.tags.size(); i++)
    {
        for (unsigned int j = 0; j < two.tags.size(); j++)
        {
            if (one.tags[i] == two.tags[j])
                common++;
        }
    }
}

int Number2Function(Image one, Image two)
{
    int common = 0;
    for (unsigned int i = 0; i < one.tags.size(); i++)
    {
        for (unsigned int j = 0; j < two.tags.size(); j++)
        {
            if (one.tags[i] == two.tags[j])
                common++;
        }
    }

    int return2 = two.tags.size() - common;
    return return2;
}
int Number3Function(Image one, Image two)
{
    int common = 0;
    for (unsigned int i = 0; i < one.tags.size(); i++)
    {
        for (unsigned int j = 0; j < two.tags.size(); j++)
        {
            if (one.tags[i] == two.tags[j])
                common++;
        }
    }

}

int getScore(Image one, Image two)
{
    
}