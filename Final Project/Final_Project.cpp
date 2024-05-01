#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <fstream>
using namespace std;

class Coordinate
{
private:
	int i, j;
public:
	Coordinate() 
	{
		i = 0;
		j = 0;

	}//Initialize the member variables to 0
	Coordinate(const int& i1, const int& j1)
	{
		i = i1;
		j = j1;

	}
	int getRowIndex() const 
	{
		return i;
	}
	int getColIndex() const 
	{
		return j;
	}
	void setRowIndex(const int& i1) 
	{
		i = i1;
	}
	void setColIndex(const int& j1) 
	{
		j = j1;
	}
	bool operator == (const Coordinate& C1) const 
	{
		if (C1.getRowIndex() == i && C1.getColIndex() == j)
			return true;
		else
			return false;
	}
	friend ostream& operator << (ostream&, const Coordinate&);
};
ostream& operator << (ostream& out, const Coordinate& c)
{
	out << "(" << c.getRowIndex() << ", " << c.getColIndex() << ")";

	return out;
}


class City
{
private:
	string name;
	int cost_right; //Although double data type would be more appropriate,
	int cost_left; //let us use int data type for easy printing purposes
	int cost_up; //This is not too important
	int cost_down; //So let's just use int data type
public:
	//Constructors
	City()
	{
		name = "";
		cost_down = -1;
		cost_left = -1;
		cost_right = -1;
		cost_up = -1;

	} //Set city to "" and all cost to -1 to mean no connection to its neighbours
	City(const string& name, const int& cost_right, const int& cost_left, const int& cost_up, const int& cost_down) 
	{
		this->name = name;
		this->cost_down = cost_down;
		this->cost_right = cost_right;
		this->cost_left = cost_left;
		this->cost_up = cost_up;

	}


	//This constructor must take the name, right, left, up, down arguments in that order
	//Getters
	string getCityName() const
	{
		return name;
	}
	int getCostRight() const
	{
		return this->cost_right;
	}
	int getCostLeft() const 
	{
		return this->cost_left;
	}
	int getCostUp() const
	{
		return this->cost_up;
	}
	int getCostDown() const
	{
		return this->cost_down;
	}
	//Setters
	void setCityName(const string&) 
	{
		this->name = name;
	}
	void setCostRight(const int& cost_right1) 
	{

		this->cost_right = cost_right1;
	}
	void setCostLeft(const int& cost_left1)
	{
		this->cost_left = cost_left1;
	}
	void setCostUp(const int& cost_up1)
	{
		this->cost_up = cost_up1;
	}
	void setCostDown(const int& cost_down1) 
	{
		this->cost_down = cost_down1;
	}
	//Friend functions
	//friend ostream& operator << (ostream&, const City&); WE Do NOT WANT THIS FUNCTION!!!
};



template <class T>
class SmarterArray
{
private:
	T* A;
	int size;
public:
	SmarterArray()
	{
		A = nullptr;
		A = new T[100];

		size = 0;
	}
	//Initialize the pointer to nullptr and the size to 0
	SmarterArray(const SmarterArray<T>& T1)
	{
		A = new T[100];
		A = T1.A;

		size = T1.size;
	}

	SmarterArray<T>& operator = (const SmarterArray<T>& T1)
	{

		A = new T[100];
		A = T1.A;

		size = T1.size;
		return *this;
	}

	~SmarterArray() 
	{


	}
	int getSize() const
	{
		return size;
	}
	T& operator[](const int& n) const 
	{

		return A[n];
	}
	bool isFound(const T& X) const 
	{
		for(int i=0;i<size;i++)
			if (A[i] == X)
			{
				return true;
			}
		return false;
	}
	void append(const T& T1)
	{


		if (A == nullptr)
		{

			if (A == nullptr)
				A = new T[100];


			A[0] = T1;


			size++;
		}
		else 
		{

			A[size] = T1;
			size++;
		}
	}
	bool remove(const int& X)
	{
		return true;
	}
	bool operator == (const SmarterArray<T>&) const;
	template <class T>
	friend ostream& operator << (ostream& out, const SmarterArray<T>& T1);
};

template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
	if (L.getSize() == 0)
		out << "[Empty Container]";
	else
	{
		out << L[0];
		for (int i = 1; i < L.getSize(); i++)
			out << " -> " << L[i];
	}
	return out;
}




ostream& operator << (ostream& out, const SmarterArray<SmarterArray<City>>& region)
{
	assert(region.getSize() > 0);
	int R = region.getSize();
	int C = region[0].getSize();
	out.setf(ios::fixed | ios::left); //Left aligned fixed decimal places
	const int width = 5;

	int i=0;
	if (i==0)
		{
			out << setw(width) << "\t";
			for (int j = 0; j < C; j++) 
			{
				out << setw(width) << region[i][j].getCostUp() << setw(width) << "\t";

			}
			out << endl << endl;
		}
		//Print the costs to move left, the city names, and the costs to move right
		for (int j = 0; j < C; j++)
		{
			//Print cost to move left only if j = 0
			if (j == 0)
				out << setw(width) << region[i][j].getCostLeft();

			out<<" ";

			out << setw(width) << region[i][j].getCityName();

			out << "    ";

			out << setw(width) << region[i][j].getCostRight();

			
		}
		out << endl << endl;
		//Print costs to move down
		out << setw(width) << "\t";
		for (int j = 0; j < C; j++) 
		{
			out << ""; out << "";

			out << setw(width) << region[i][j].getCostDown() << setw(width) << "\t";

		}
		out << endl;

	for (int i = 1; i < R; i++)
	{
		out << endl;
		

		//Print the costs to move up only if i = 0
		if (i == 0)
		{
			out << setw(width) << "\t";
			for (int j = 0; j < C; j++) 
			{
				out << setw(width) << region[i][j].getCostUp() << setw(width) << "\t";

			}
			out << endl << endl;
		}
		//Print the costs to move left, the city names, and the costs to move right
		for (int j = 0; j < C; j++)
		{
			//Print cost to move left only if j = 0
			if (j == 0)
				out << setw(width) << region[i][j].getCostLeft();

			out << setw(width) << region[i][j].getCityName();

			out << "  ";

			out << setw(width) << region[i][j].getCostRight();

			
		}
		out << endl << endl;
		//Print costs to move down
		out << setw(width) << "\t";
		for (int j = 0; j < C; j++) 
		{
			out << ""; out << "";

			out << setw(width) << region[i][j].getCostDown() << setw(width) << "\t";

		}
		out << endl;
	}
	out.unsetf(ios::fixed | ios::left); //Removing formatting
	out.precision(0); //Resetting the decimal places
	return out;
}


int computePathCost(const SmarterArray<SmarterArray<City>>& region_map, const SmarterArray<Coordinate>&
	path)
{
	int cost = 0;
	for (int i = 0; i < path.getSize() - 1; i++)
	{
		int i1 = path[i].getRowIndex();
		int j1 = path[i].getColIndex();
		int i2 = path[i + 1].getRowIndex();
		int j2 = path[i + 1].getColIndex();
		if (i2 == i1 - 1)
			cost += region_map[i1][j1].getCostUp();
		else if (i2 == i1 + 1)
			cost += region_map[i1][j1].getCostDown();
		else if (j2 == j1 + 1)
			cost += region_map[i1][j1].getCostRight();
		else
			cost += region_map[i1][j1].getCostLeft();
	}
	return cost;
}

SmarterArray<Coordinate> computeMinimumCostPath(const SmarterArray<SmarterArray<City>>& region_map, const
	SmarterArray<SmarterArray<Coordinate>>& all_paths)
{
	SmarterArray<Coordinate> minCostPath = all_paths[0];
	int minCost = computePathCost(region_map, minCostPath);
	for (int i = 1; i < all_paths.getSize(); i++)
	{
		int cost = computePathCost(region_map, all_paths[i]);
		if (cost < minCost)
		{
			minCostPath = all_paths[i];
			minCost = cost;
		}
	}
	return minCostPath;
}

void computeAllPossiblePaths(const SmarterArray<SmarterArray<City>>& region_map, const Coordinate&
	departure, const Coordinate& destination, SmarterArray<SmarterArray<Coordinate>>& all_paths,
	SmarterArray<Coordinate> path = SmarterArray<Coordinate>())
{

	assert(region_map.getSize() > 0);
	int i1 = departure.getRowIndex();
	int j1 = departure.getColIndex();
	int i2 = destination.getRowIndex();
	int j2 = destination.getColIndex();


	assert(i1 >= 0 && i1 < region_map.getSize() && j1 >= 0 || j1 < region_map[0].getSize());
	//cout << "Visiting... " << departure << endl;
	path.append(departure);

	//cout << "The path so far is: " << path << endl;system("Pause");
	if (i1 == i2 && j1 == j2) //The departure and destination coordinates are equal.
	{
		cout << endl << "Path found: " << path << endl << endl;
		all_paths.append(path);

		return;
	}
	else
	{
		if (region_map[i1][j1].getCostUp() != -1)
		{
			if (!path.isFound(Coordinate(i1 - 1, j1)))
			{
				computeAllPossiblePaths(region_map, Coordinate(i1 - 1, j1), destination,
					all_paths, path);
				//cout << "Erasing1 " << path[path.getSize()-1] << endl;
				path.remove(path.getSize() - 1);
				//cout << "The path so far is: " << path<< path.getSize() << endl;system("Pause");
			}
		}
		if (region_map[i1][j1].getCostRight() != -1)
		{
			if (!path.isFound(Coordinate(i1, j1 + 1)))
			{
				computeAllPossiblePaths(region_map, Coordinate(i1, j1 + 1), destination,
					all_paths, path);
				//cout << "Erasing2 " << path[path.getSize()-1] << endl;
				path.remove(path.getSize() - 1);
				//cout << "The path so far is: " << path<< path.getSize() << endl;system("Pause");
			}
		}
		if (region_map[i1][j1].getCostDown() != -1)
		{
			if (!path.isFound(Coordinate(i1 + 1, j1)))
			{
				computeAllPossiblePaths(region_map, Coordinate(i1 + 1, j1), destination,
					all_paths, path);
				//cout << path.getSize();
				//cout << "Erasing3 " << path[path.getSize()-1] << endl;
				path.remove(path.getSize() - 1);
				//cout << "The path so far is: " << path<< path.getSize() << endl;system("Pause");
			}
		}
		if (region_map[i1][j1].getCostLeft() != -1)
		{
 			if (!path.isFound(Coordinate(i1, j1 - 1)))
			{
				computeAllPossiblePaths(region_map, Coordinate(i1, j1 - 1), destination,
					all_paths, path);
				//cout << "Erasing4 " << path[path.getSize()-1] << endl;
				path.remove(path.getSize() - 1);
				//cout << "The path so far is: " << path<< path.getSize() << endl;system("Pause");
			}
		}
	}
}

/*

int main()
{
	//Seed the random number generator
	srand(1);

	//Declare the region map
	SmarterArray<SmarterArray<City>> region_map;

	//Construct the region map with specified size and connectivity information
	const int R = 20;
	const int C = 20;
	double linkProbability = 0.49; //Increment from 0.48 up to get fewer paths OR decrement to get more paths
	for (int i = 0; i < R; i++)
	{
		SmarterArray<City> row_map;
		for (int j = 0; j < C; j++)
		{
			string city_name = "";
			city_name += char(65+i);
			city_name += char(65+j);
			int cost_up = (i == 0 ? -1 : (1.0*rand()/RAND_MAX < linkProbability ? -1 : rand() % 5 + 1));
			int cost_right = (j == C-1 ? -1 : (1.0*rand()/RAND_MAX < linkProbability ? -1 : rand() % 5 + 1));
			int cost_down = (i == R-1 ? -1 : (1.0*rand()/RAND_MAX < linkProbability ? -1 : rand() % 5 + 1));
			int cost_left = (j == 0 ? -1 : (1.0*rand()/RAND_MAX < linkProbability ? -1 : rand() % 5 + 1));
			row_map.append(City(city_name, cost_right, cost_left, cost_up, cost_down));
		}
		region_map.append(row_map);
		row_map.~SmarterArray();
	}
	cout << "The region map is..." << endl << region_map << endl << endl;

	//Select the departure and destination coordinates
	Coordinate departure(rand()%20, rand()%20);
	Coordinate destination(rand()%20, rand()%20);
	cout << "Departing from " << departure << endl << endl;
	cout << "Destined to " << destination << endl << endl;

	//Compute all the possible paths
	SmarterArray<SmarterArray<Coordinate>> all_paths;
	computeAllPossiblePaths(region_map, departure, destination, all_paths);

	//Print all the possible paths
	cout << endl << "All the paths computed are..." << endl;
	for (int i = 0; i < all_paths.getSize(); i++)
		cout << all_paths[i] << endl;

	//Print the minimum cost path
	SmarterArray<Coordinate> minCostPath = computeMinimumCostPath(region_map, all_paths);
	cout << endl << "The minimum cost path is " << endl << minCostPath << endl << endl;
	cout << "It's cost = " << computePathCost(region_map, minCostPath) << endl << endl;

	//Finish the program
	system("Pause");
	return 0;
}
*/



int main()
{
	//Create the region map
	SmarterArray<SmarterArray<City>> region_map;
	SmarterArray<City> row0_map[30];
	string city;
	ifstream myfile;

	cout << "Reading from Region_Map.txt file..." << endl;
	myfile.open("Region_Map.txt");
	int a;
	int b;
	myfile >> a;
	myfile >> b;
	string citiii[100];
	int nr=0;
	
	string p[100][100];
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++) 
		{
			myfile >> city;
			citiii[nr] = city;
			nr++;
			row0_map[i].append(City(city, -1, -1, -1, -1));
		}
		region_map.append(row0_map[i]);
		row0_map[i].~SmarterArray();
	}
	myfile.close();

	string city1;
	string city2;
	int dist;

	cout << "Done!" << endl;

	cout << "Reading from Connectivity_Map.txt file..." << endl;
	myfile.open("Connectivity_Map.txt");
	while (!myfile.eof()) 
	{
		myfile >> city1;
		myfile >> city2;
		myfile >> dist;
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++) 
			{

				if (region_map[i][j].getCityName() == city1) 
				{
					if (i > 0)
					{
						if (region_map[i - 1][j].getCityName() == city2)
						{
							region_map[i ][j].setCostUp(dist);
							region_map[i - 1][j].setCostDown(dist);

						}
					}

					if (i < a)
					{
						if (region_map[i + 1][j].getCityName() == city2) 
						{
							region_map[i ][j].setCostDown(dist);
							region_map[i + 1][j].setCostUp(dist);

						}

					}
					if (j > 0)
					{
						if (region_map[i][j - 1].getCityName() == city2) 
						{
							region_map[i][j].setCostLeft(dist);
							region_map[i][j - 1].setCostRight(dist);

						}

					}
					if (j < b)
					{
						if (region_map[i][j + 1].getCityName() == city2)
						{
							region_map[i][j].setCostRight(dist);
							region_map[i][j + 1].setCostLeft(dist);

						}

					}

				}

			}
		}
	}
	cout << "Done!"<<endl<<endl;
	myfile.close();

	cout << "The region map is..." << endl <<endl << region_map << endl << endl;
	//Select the departure and destination cities

	string depart1;
	string destination1;
	cout << "Enter a departure city: ";
	cin >> depart1;
	cout <<endl;
	cout << "Enter a destination city: ";
	cin >> destination1;
	cout << endl;
	int c;
	int d;
	for (int i = 0; i < nr; i++)
	{
		if (citiii[i] == depart1)
		{
			c = i % b;
			d = i / b;
		}
	}
	Coordinate departure(d, c);
	for (int i = 0; i < nr; i++) 
	{
		if (citiii[i] == destination1) 
		{
			c = i % b;
			d = i / b;
		}
	}
	Coordinate destination(d, c);

	cout << "Departing from " << departure << endl << endl;
	cout << "Destined to " << destination << endl << endl;

	//Compute all the possible paths
	SmarterArray<SmarterArray<Coordinate>> all_paths;
	computeAllPossiblePaths(region_map, departure, destination, all_paths);
	//Print all the possible paths
	cout << endl << "All the paths computed are..." << endl;
    for (int i = 0; i < all_paths.getSize(); i++)
	{ 
		for (int j = 0; j < all_paths[i].getSize(); j++) 
		{
			if(i==0 && j==3)
				cout << region_map[all_paths[i][j].getColIndex()][all_paths[i][j].getRowIndex()].getCityName();
			else
				cout << region_map[all_paths[i][j].getRowIndex()][all_paths[i][j].getColIndex()].getCityName();

			if (j < all_paths[i].getSize()-1)
			{
				cout << "->";
			}

		}
		cout << endl;
	}
	//Print the minimum cost path
	SmarterArray<Coordinate> minCostPath = computeMinimumCostPath(region_map, all_paths);
	cout << endl << "The minimum cost path is ";
	
	if (minCostPath.getSize()!=0)
	{
		for (int j = 0; j < minCostPath.getSize(); j++)
		{
			cout << region_map[minCostPath[j].getRowIndex()][minCostPath[j].getColIndex()].getCityName();
			if (j < minCostPath.getSize() - 1)
			{
				cout << "->";
			}
		}
	}
	else
		cout<<endl<<minCostPath;

	cout <<endl << endl << "It's cost = " << computePathCost(region_map, minCostPath) << endl << endl;
	//Finish the program
	system("Pause");
	return 0;
}
