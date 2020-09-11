#include <iostream>
#include <string>
#include <vector>
#include "undirectedGraph.h" 

using namespace std;



int main()
{

    uGraph test;

    //variables for iunputs
    string command;

    string args;
    string arg1;
    string arg2;
    double arg3;

    //variable to store the position of the delimiter
    int pos;

    string inputLine;

    getline(cin, inputLine);

    while(!cin.eof())
    {

    
        //extract the command string
        //finding the position of the ;
        pos = inputLine.find(" ");


        //this is the case where the commands has arguments
        //since if there is a space delimiter, pos will not return -1
        if(pos != -1)
        {
            
            //setting the command string
            command = inputLine.substr(0, pos);

            if(command == "i")
            {
                
                
                //delete the command string and store the argument city
                arg1 = inputLine.erase(0, pos + 1);

                //checks to see if the city is in the graph first
                bool isCityThere = test.searchName(arg1);

                //if it is dont insert and print faulure
                if(isCityThere == true)
                {
                    cout << "failure" << endl;
                }

                //if city is not in graph insert and print success
                if(isCityThere == false)
                {
                    test.insertCity(arg1);
                    cout << "success" << endl;
                }

                
            }
            
            if(command == "setd")
            {
                
                //delete the command string and store the arguments
                args = inputLine.erase(0, pos + 1);

                //extracting the params in this case there are 3
                for(int i = 0; i < 3; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = args.substr(0, pos);
                    }
                    else if(i == 1)
                    {
                        arg2 = args.substr(0, pos);
                    }
                    else if(i == 2)
                    {
                        arg3 = stod(args.substr(0, pos));
                    }
                    
                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);

                }

                //setting the distance, the actual function deals with printing and edge cases
                //such as same city name, the cities dont exist or d is invalid
                test.setDistance(arg1, arg2, arg3);

            }

            if(command == "s")
            {
                bool isCityThere;

                 //delete the command string and store the argument city
                arg1 = inputLine.erase(0, pos + 1);


                isCityThere = test.searchName(arg1);
                
                if(isCityThere == true)
                {
                    cout << "found " + arg1 << endl;
                }

                if(isCityThere == false)
                {
                    cout << "not found" << endl;
                }


            }

            if(command == "degree")
            {

                //delete the command string and store the argument city
                arg1 = inputLine.erase(0, pos + 1);

                test.nodeDegree(arg1);

            }

            if(command == "d")
            {

                //delete the command string and store the arguments
                args = inputLine.erase(0, pos + 1);

                //extracting the params in this case there are 2
                for(int i = 0; i < 2; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = args.substr(0, pos);
                    }
                    else if(i == 1)
                    {
                        arg2 = args.substr(0, pos);
                    }
                    
                    
                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);
                }


                test.printDistance(arg1, arg2);

            }

            if(command == "shortest_d")
            {

                //delete the command string and store the arguments
                args = inputLine.erase(0, pos + 1);

                //extracting the params in this case there are 2
                for(int i = 0; i < 2; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = args.substr(0, pos);
                    }
                    else if(i == 1)
                    {
                        arg2 = args.substr(0, pos);
                    }
                    
                    
                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);
                }


                test.shortestDistance(arg1, arg2);

            }

            if(command == "print_path")
            {

                //delete the command string and store the arguments
                args = inputLine.erase(0, pos + 1);

                //extracting the params in this case there are 2
                for(int i = 0; i < 2; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = args.substr(0, pos);
                    }
                    else if(i == 1)
                    {
                        arg2 = args.substr(0, pos);
                    }
                    
                    
                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);
                }


                test.printPath(arg1, arg2);

            }



        }

        //this is the case where the commands has no arguments, pos will return -1
        if(pos == -1)
        {

            if(inputLine == "graph_nodes")
            {
                cout << "number of nodes " + to_string(test.getNumNodes()) << endl;
            }

            if(inputLine == "graph_edges")
            {
                cout << "number of edges " + to_string(test.getNumEdges()) << endl;
            }

            if(inputLine == "clear")
            {
                test.clearGraph();
            }

        }


        getline(cin, inputLine);
    }


}