//  dsf34--Darren Fahy
//
//  main.cpp
//  BinarySearchTree
//
//

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Tree.h"


using namespace std;

int main(int argc, const char * argv[])
{
    ifstream inFile;
    ifstream lFile;
    string file_path;
    string line;

    if (argc < 2)
    {
        cout << "Not enough command line arguments";
    }
    else
    {
        file_path = argv[1];
        inFile.open(file_path.c_str());
        string input;
        string command;
        string value;
        
        Tree<char*> myTree;
        
        while (!inFile.eof())
        {
            getline(inFile, line);
            stringstream ss(line);
            
            if (line.size() == 2)
            {
                while (ss >> command)
                {
                    cout << command << endl;
                    
                    if (command == "#E")
                    {
                        myTree.empty();
                    }
                    if (command == "#T")
                    {
                        //terminate program
                        cout << "\nProgram Terminating\n" << endl;
                        return 0;
                    }
                }//end while ss>>command
            }//
            else
            {
                while (ss >> command >> value)
                {
                    cout << "Command:" << command << " Value:" << value << endl;
                    
                    if ( command == "#L")
                    {
                        lFile.open(value);
                        while (!lFile.eof())
                        {
                            while (getline(lFile, input))
                            {
                                istringstream ss(input);
                                while(ss >> value)
                                {
                                    char * cval = new char [value.length()+1];
                                    std::strcpy (cval, value.c_str());
                                    myTree.insert(cval);
                                }
                            }//end while getline
                            
                        }//end while eof
                        
                    }//end if #L
                    if (command == "#A")
                    {
                        char * cval = new char [value.length()+1];
                        std::strcpy (cval, value.c_str());
                        myTree.insert(cval);
                    }
                    if (command == "#D")
                    {
                        cout << "Deleting this from tree: " << value << endl;
                        char * cval = new char [value.length()+1];
                        std::strcpy (cval, value.c_str());
                        myTree.remove(cval);
                    }
                    if (command == "#F")
                    {
                        char * cval = new char [value.length()+1];
                        std::strcpy (cval, value.c_str());
                        if ( myTree.nodeHeight(cval) < 0)
                        {
                            cout << "Value: " << value << " not found in tree" << endl;
                        }
                        else
                            cout << "Height of " << value << " is: " << myTree.nodeHeight(cval) << endl;
                    }
                    if (command == "#PI")
                    {
                        myTree.writeFilepi(value);
                    }
                    if (command =="#PP")
                    {
                        myTree.writeFilepp(value);
                    }
                    if (command == "#PE")
                    {
                        myTree.writeFilepe(value);
                    }
                    if (command == "#H")
                    {
                        //cout << myTree.treeHeight() << endl;//height of root
                        myTree.writeFileth(value);
                    }
                    
                }//end while ss >> c >> v
            }//end while
        }//end else
    }//end else
    
    return 0;
}
