#include <iostream>
#include <string>
#include <vector>
#include "Dijkstra.h" 

using namespace std;



class uGraph
{
    private:
        
        int numNodes;
        int numEdges;
    

        //2d vector to store the dynamically sized undirected graph as an adjacency matrix
        vector<vector<double>> graph;

        //This will store the city index informations for the adjacency matrix
        vector<string> cityIndex;

        //this will be used for the functions in the dijkstra class
        dijkstra *eval;

        //this is to hold the final data from djikstras function
        vector<Triplet> finalData;

    public:
        
        //constructor
        uGraph()
        {
            numNodes = 0;
            numEdges = 0;
        }
        
        //destructor is not needed since I delete the eval pointer in
        //the dijktras function itself.
    
    void insertCity(string name)
    {
       
        //add the new city name to the city
        cityIndex.push_back(name);

        //resize the adjacency matrix to include the city added
        numNodes++;

        //adding a row to the adjacency matrix
        graph.push_back(vector<double>());
        
        //adding a column to the adjacency matrix
        for(int i = 0; i < graph.size(); ++i)
        {
            graph[i].resize(numNodes);
        }

    
    }

    void setDistance(string name1, string name2, double distance)
    {
        //this will determine if both cities exist in the vector of cities
        int exist = 0;

        //the indexes are to store the indexes of the cities if they exist so
        //we can locate them in the adjacency matrix        
        int index1;
        int index2;

        //if d <= 0 pring failure and return
        //***********REMEBER TO ADD EDGE CASES HERE SUCH AS NODE IS LESS 1 or less
        if(distance <= 0 || name1 == name2 || numNodes < 2)
        {
            cout << "failure" << endl;
            return;
        }

        //checks to see if the two cities exist
        for(int i = 0; i < cityIndex.size(); i++)
        {
            //if one of the cities exist increment exist and save the cities
            //index value to use for the adjacency matrix
            if(cityIndex[i] ==  name1)
            {
                exist++;
                index1 = i;
            }

            if(cityIndex[i] ==  name2)
            {
                exist++;
                index2 = i;
            }
        }

        //if both cities do not exist in the vector of cities return failure
        if(exist < 2)
        {
            cout << "failure" << endl;
            return;
        }
        //else set the distance between the two cities
        else if(exist == 2)
        {

            //If there is no edges currently in the matrix at this location we increment numEdges
            //This if statement is used to prevent the case where we simply replace the weight of an existing edge
            if(graph[index1][index2] == 0)
            {
                numEdges++;
            }

            graph[index1][index2] = distance;
            graph[index2][index1] = distance;

            cout << "success" << endl;

        }
        

    }

    //This methods checks if the city is in the graph
    bool searchName(string name)
    {
        bool isfound = false;

        //check if the city exists in the vector of cities
        for(int i = 0; i < cityIndex.size(); i++)
        {
            
            if(cityIndex[i] ==  name)
            {
                isfound = true;
                return isfound;
            }

        }

        return isfound;

    }

    void nodeDegree(string name)
    {
        bool exist = false;
        int index;

        for(int i = 0; i < cityIndex.size(); i++)
        {
            //if the city exist increment exist and save the city's
            //index value to use for the adjacency matrix
            if(cityIndex[i] ==  name)
            {
                exist = true;
                index = i;
            }

        }

        //If the name does not exist in the graph of the graph is empty print failure
        //and return
        if(exist == false || numNodes == 0)
        {
            cout << "failure" << endl;
            return;
        }

        //if the name is in the graph we will find the degree
        if(exist == true)
        {

            int degree = 0;

            //iterate through the columns of the row n to count++ the number of edges connected to the node
            for(int j = 0; j < numNodes; j++)
            {
                    
                if(graph[index][j] > 0)
                {
                    degree++;
                }
            }

            cout << "degree of " + name + " " + to_string(degree) << endl;

        }
        
    }

    //this method print the distance between two adjacent cities
    void printDistance(string name1, string name2)
    {
        //this will determine if both cities exist in the vector of cities
        int exist = 0;

        //the indexes are to store the indexes of the cities if they exist so
        //we can locate them in the adjacency matrix        
        int index1;
        int index2;
        double distance;

        //if the two city names are the same pring failure then return
        if(name1 == name2)
        {
            cout << "failure" << endl;
            return;
        }

        //checks to see if the two cities exist
        for(int i = 0; i < cityIndex.size(); i++)
        {
            //if one of the cities exist increment exist and save the cities
            //index value to use for the adjacency matrix
            if(cityIndex[i] ==  name1)
            {
                exist++;
                index1 = i;
            }

            if(cityIndex[i] ==  name2)
            {
                exist++;
                index2 = i;
            }
        }

        //if both cities do not exist in the vector of cities return failure
        if(exist < 2)
        {
            cout << "failure" << endl;
            return;
        }
        //if they do exist check if they are connected
        else if(exist = 2)
        {
            //if the two cities are not connected returna and print failure
            if(graph[index1][index2] == 0)
            {
                cout << "failure" << endl;
                return;
            }
            //if they are connected print the distance between them
            else if(graph[index1][index2] > 0)
            {
                distance = graph[index1][index2];

                cout << "direct distance " << name1 << " to " << name2 << " " << distance << endl;
                return;
            }
            


        }

    }


    //This method will pass the necessary info along to the dijkstra class to be proccessed for
    //the commands of shortest_d and print_path
    void doDijkstra(string startingVertex)
    {
        eval = new dijkstra(graph, cityIndex, startingVertex);
        
        eval -> calcDijkstra();

        //passing back the processed data from the djikstras algorithm
        finalData = eval -> currData;

        //delete eval
        delete eval;
        
    }

    //This method will print the shortest distance between two cities
    void shortestDistance(string name1, string name2)
    {
        //this will determine if both cities exist in the vector of cities
        int exist = 0;

        //this wi,ll hold the shortest distance if there is one
        double sDistance;

        //the indexes are to store the indexes of the cities if they exist so
        //we can locate them in the adjacency matrix        
        int index1;
        int index2;

        //if the two names are the same porint failure and exit
        if(name1 == name2)
        {
            cout << "failure" << endl;
            return;
        }

        //checks to see if the two cities exist
        for(int i = 0; i < cityIndex.size(); i++)
        {
            //if one of the cities exist increment exist and save the cities
            //index value to use for the adjacency matrix
            if(cityIndex[i] ==  name1)
            {
                exist++;
                index1 = i;
            }

            if(cityIndex[i] ==  name2)
            {
                exist++;
                index2 = i;
            }
        }

        //if both cities that were in the paramters are not in the graph then priont failure and exit
        if(exist < 2)
        {
            cout << "failure" << endl;
            return;
        }

        //calculating the shortest distance between the two cities
        doDijkstra(name1);

       
        if(finalData[index2].isInfinite == false)
        {
            //since the graph is connected  we set the sDistance to the value of name 2
            sDistance = finalData[index2].shortestD;
            cout << "shortest distance " << name1 << " to " << name2 << " " << sDistance << endl; 
            return;
        }
        else if(finalData[index2].isInfinite == true)
        {
            cout << "failure" << endl;
            //cout << previous << endl;
            return;
        }

    }

    //This method will print the path between two cities
    void printPath(string name1, string name2)
    {

        //this will determine if both cities exist in the vector of cities
        int exist = 0;

        //this will hold the cities in the shortest path
        vector<string> pathCities;

        //the indexes are to store the indexes of the cities if they exist so
        //we can locate them in the adjacency matrix        
        int index1;
        int index2;

        //if the two names are the same porint failure and exit
        if(name1 == name2)
        {
            cout << "failure" << endl;
            return;
        }

        //checks to see if the two cities exist
        for(int i = 0; i < cityIndex.size(); i++)
        {
            //if one of the cities exist increment exist and save the cities
            //index value to use for the adjacency matrix
            if(cityIndex[i] ==  name1)
            {
                exist++;
                index1 = i;
            }

            if(cityIndex[i] ==  name2)
            {
                exist++;
                index2 = i;
            }
        }

        //if both cities that were in the paramters are not in the graph then priont failure and exit
        if(exist < 2)
        {
            cout << "failure" << endl;
            return;
        }

        //calculating the shortest distance between the two cities
        doDijkstra(name1);

        
        //this string will be used to store the previous data
        string previous = finalData[index2].preVertex;

        //this will store the current string and we initalize it to the seconds city
        string current = name2;

        //this will store the current cities index
        int currIndex;
        
        //this will loop until we hit the starting vertex or the current vertex is not connected
        //to anything in both cases they equal "" so we end the loop
        while(previous != "")
        {
            

            //finds the index of the current city
            for(int i = 0; i < cityIndex.size(); i++)
            {
                //if one of the cities exist increment exist and save the cities
                //index value to use for the adjacency matrix
                if(cityIndex[i] ==  previous)
                {
                    currIndex = i;
                }
            }
            
            //adding the vertexes shortest distance to the starting vertex
            //sDistance = sDistance + finalData[currIndex].shortestD;

            //setting the previous vertex to the currentvertexes previous vertex
            previous = finalData[currIndex].preVertex;

            //setting the current to the previous
            current = finalData[currIndex].cityName;

            //pushing the current city to the path of cities
            pathCities.push_back(current);

            //cout << current << endl;

        } 

        //this checks if the the two cities are connected or not.
        //If thy are then the final current value will equal to name1.
        //If that is the case we print the shortest distance.
        //If not we output failure since the two cities are not conneccted.

        if(current == name1)
        {
            
            //now print the rest of the cities in the path following the starting city
            for(int i = pathCities.size(); i > 0; i--)
            {
                //print the path of cities if they are connected
                cout << pathCities[i - 1] + " ";
            
            }

            //print the final city
            cout << finalData[index2].cityName << endl;
             
            return;
        }
        else if(current != name1)
        {
            cout << "failure" << endl;
            //cout << previous << endl;
            return;
        }


    }

    //This method will clear the nodes and edges from the graph
    void clearGraph()
    {

        //need to clear cityIndex 1d vector and graph 2d vector and
        //also reset node and edge count

        cityIndex.clear();
        graph.clear();

        numEdges = 0;
        numNodes = 0;

        cout << "success" << endl;

    }


    int getNumEdges()
    {
        return numEdges;
    }

    int getNumNodes()
    {
        return numNodes;
    }
    

};

