#include <iostream>
#include <string>
#include <vector>

using namespace std;

//This struct will hold the shortest distance from the starting vertex and
//the previous vertex and if the vertex is infinite or not, and the city name
//and whether it has been visted or not
struct Triplet
{
    string cityName;
    double shortestD;
    string preVertex;
    bool isInfinite;
    bool isVisted;
};

class dijkstra
{

    private:

    public:
        
        string startingVert;

        //this will hold the adjacency matrix created by the undirectedGraph class
        vector<vector<double>> dijGraph;

        //this will hold the vector of cities created by the undirectedGraph class
        vector<string> dijCityIndex;

        //this will hold the previous/parent vertex and 
        //shortest distance from the startong vertex
        vector<Triplet> currData;

        //This will hold the current index
        int currIndex; 



        dijkstra(vector<vector<double>> dG, vector<string> dCI, string sV)
        {
            //intializing the member variables with the information passed along from the undirectedGraph class
            dijGraph = dG;
            dijCityIndex = dCI;
            startingVert = sV;

            //initializing the all vertex lengths to be infinite and parents to null
            for(int i = 0; i < dijCityIndex.size(); i++)
            {
                //note it doesnt really matter what distance we initialize the shortestD value
                //since we have a boolean determining it he vertex has infinite or not
                currData.push_back({dijCityIndex[i], 8 , "" , true, false});
            }
        }


        //this method will calculate the minimum vertex in the unfound set



        //This method will calculate all the values such as shortest distance from
        //starting vertex previous vertex for each vertex
        void calcDijkstra()
        {
            //search which index the startingVertex is
            for(int i = 0; i < dijCityIndex.size(); i++)
            {
                if(startingVert == currData[i].cityName)
                {
                    currIndex = i;
                    break;
                }
            }

            //set the starting vertex to 0 and removing infinite flag
            currData[currIndex].isInfinite = false;
            currData[currIndex].shortestD = 0;

            //this will keep track of the number of cities visted
            int visitedCounter = 0;

            //this will keep track of the smallest current distance to be extracted
            double smallestDist;


            
            //continue the loop while the number of citiees visted equals the total
            //number of cities
            while(visitedCounter < dijCityIndex.size())
            {

                //flag for determining if we have our first distance for 
                //smallestDist or not
                bool hasDistance = false;

                //extract the vertex with the minimum distance that is in
                //the unvisted set it will be saved in currIndex
                for(int i = 0; i < dijCityIndex.size(); i++)
                {
                    if(currData[i].isInfinite == false && currData[i].isVisted == false)
                    {
                        //This tests to see if the smallestDistance has a value or not
                        //from the current for loop
                        if(hasDistance == false)
                        {
                            smallestDist = currData[i].shortestD;
                            currIndex = i;

                            //since we now have a distance from the current for loop
                            //we will remove the flag
                            hasDistance = true;
                        }

                        if(currData[i].shortestD < smallestDist)
                        {
                            smallestDist = currData[i].shortestD;
                            currIndex = i;
                        }


                    }
                }

                //For the above if the graph is not completely connected it will just keep looping
                //at the last vertex that was connected until the while loop ends


                //add the extracted vertex to the visted vertex set and increment vistedCounter
                currData[currIndex].isVisted = true;
                visitedCounter++;

                //for each of the unvisted adjacent vertexes update their shortestDist from
                //the starting vertex if its lower than what was previously recoreded
                //If we updated the above vertex then we also update their previous/parent vertex as well
                for(int i = 0; i < dijCityIndex.size(); i++)
                {
                    //if it is an ajacent city it will have an connected dge greater than 0
                    if(dijGraph[currIndex][i] > 0)
                    {

                        //This is for if the adjacent vertex's shortest distance is currently infinite
                        if(currData[i].isInfinite == true)
                        {
                            //set the infinite flag to false
                            currData[i].isInfinite = false;

                            //set the adjacent vertex shortest distance to the current vertex's value + the adjacent edge value
                            currData[i].shortestD = currData[currIndex].shortestD + dijGraph[currIndex][i];

                            //set the previous vertex of the adjacent vertex to the current vertex
                            currData[i].preVertex = currData[currIndex].cityName;

                        }
                        //This is for cases where the adjacent matrix's shortest distanc is not infinite
                        //Calculate the distance of each neighbour from the start index with the value
                        //of the current vertice + the adjacent edge value. 
                        //If the calculated distance is shorter than the known
                        //distance, update the shortest distance for the current adjacent vertex
                        else if((currData[currIndex].shortestD + dijGraph[currIndex][i] < currData[i].shortestD) && currData[i].isInfinite == false)
                        {
                            //set the adjacent vertex shortest distance to the current vertex's value + the adjacent edge value
                            currData[i].shortestD = currData[currIndex].shortestD + dijGraph[currIndex][i];
                            
                            //set the previous vertex of the adjacent vertex to the current vertex
                            currData[i].preVertex = currData[currIndex].cityName;
                        }

                    }

                }



            }


        }

        



};