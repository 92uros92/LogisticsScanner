#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "iomanip"

const int MATERIAL_WIDTH = 25;
const int DEMARCATION_WIDTH = 115;

class material
{
public:
    int ID_material;
    std::string material_description;
    int handling_unit;
    int material_location;

};


void ScannerRead(std::vector <material>& v_mat);
void printMenu();
void doTask(std::vector<material>& v_mat, int option);
void printMaterial(material m);
int searchMaterial(std::vector <material> v_mat, int targetMaterial);
int searchHU(std::vector<material> v_mat, int targetHU);
int printLocation(material l);
void addMaterial(std::vector<material>& v_mat);
void saveMaterial(std::vector <material> v_mat);


void ScannerRead(std::vector <material>& v_mat)
{
    std::ifstream read_from_scanner("material.txt");
    if (!read_from_scanner)
    {
        std::cout << "Unable to open file material.txt\n";
        exit(1);
    }

    std::string line;
    int recordNumbers = 0;
    while (!read_from_scanner.eof())
    {
        std::getline(read_from_scanner, line);
        recordNumbers ++;
        
            // Read from file.
        
        //std::cout << recordNumbers << " - " << line << "\n";

        std::istringstream iss(line);

        std::string strID_material;
        std::string strMaterial_description;
        std::string strHandling_unit;
        std::string strMaterial_location;

        std::getline(iss, strID_material, ',');
        std::getline(iss, strMaterial_description, ',');
        std::getline(iss, strHandling_unit, ',');
        std::getline(iss, strMaterial_location, ',');

        material temp;
        temp.ID_material = atoi(strID_material.c_str());
        temp.material_description = strMaterial_description;
        temp.handling_unit = atoi(strHandling_unit.c_str());
        temp.material_location = atoi(strMaterial_location.c_str());

        v_mat.push_back(temp);
    }
    read_from_scanner.close();

}

void printMenu()
{
    std::cout << "1.) MATERIAL ID" << "\n";
    std::cout << "2.) ADD MATERIAL" << "\n";
    std::cout << "3.) SEARCH LOCATION" << "\n";
    std::cout << "4.) EXIT" << "\n";
}

void doTask(std::vector<material>& v_mat, int option)
{
    switch (option)
    {
    case 1:
        std::cout << "Please enter Handling Unit: " << "\n";
        int targetHU;
        int indexHU;
        std::cin >> targetHU;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        indexHU = searchHU(v_mat, targetHU);
        if (indexHU == -1)
        {
            std::cout << "Handling Unit " << targetHU << " does not exists!" << "\n";
        }
        else
        {
            printMaterial(v_mat[indexHU]);
        }
      
        break;
    case 2:
        addMaterial(v_mat);
        break;
    case 3:
        std::cout << "Please enter material ID: " << "\n";
        int targetMaterial;
        int indexID;
        std::cin >> targetMaterial;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        indexID = searchMaterial(v_mat, targetMaterial);
        if (indexID == -1)
        {
            std::cout << "Material " << targetMaterial << " does not exists!" << "\n";
        }
        else
        {
            int loc = printLocation(v_mat[indexID]);
            std::cout << "Location for material " << targetMaterial << " is: " << loc << "\n";
            
        }
        break;
    default:
        std::cout << "Incorrect program selection.\n"
                    << "Select a menu from 1 to 4.\n";
        break;
    }
}

void printMaterial(material m)
{
    std::cout << "\n";
    // Header
    std::cout << std::setw(MATERIAL_WIDTH) << std::left << "Ident"
              << std::setw(MATERIAL_WIDTH) << std::left << "Material Description"
              << std::setw(MATERIAL_WIDTH) << std::left << "Handling Unit"
              << std::setw(MATERIAL_WIDTH) << std::left << "Location"
              << "\n\n";
    
    // Demarcation line

    std::cout << std::setw(DEMARCATION_WIDTH) << std::setfill('-') << " " << "\n";
    std::cout << std::setfill(' ') << "\n";

    // Body

    std::cout << std::setw(MATERIAL_WIDTH) << std::left << m.ID_material
        << std::setw(MATERIAL_WIDTH) << std::left << m.material_description
        << std::setw(MATERIAL_WIDTH) << std::left << m.handling_unit
        << std::setw(MATERIAL_WIDTH) << std::left << m.material_location
        << "\n\n";

    // Demarcation line

    std::cout << std::setw(DEMARCATION_WIDTH) << std::setfill('-') << " " << "\n";
    std::cout << std::setfill(' ');

    std::cout << "\n";
}

void addMaterial(std::vector<material>& v_mat)
{
    material temp;
    bool isDuplicate = false;

    do
    {
        std::cout << "Please enter handling unit: " << "\n";
        std::cin >> temp.handling_unit;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        isDuplicate = false;
        if (searchHU(v_mat, temp.handling_unit) != -1)
        {
            isDuplicate = true;
            std::cout << "Handling unit " << temp.handling_unit << " already exists." << "\n";
            std::cout << "Please enter another HU." << "\n";
        }

    } while (isDuplicate);
    
        std::cout << "Material: ";
        std::cin >> temp.ID_material;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        std::cout << "Material description: ";
        std::cin >> temp.material_description;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        std::cout << "Handling Unit: ";
        std::cin >> temp.handling_unit;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        std::cout << "Material location: ";
        std::cin >> temp.material_location;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        v_mat.push_back(temp);

        std::cout << "Material: " << temp.ID_material << " successfully added." << "\n\n";
        std::cout << "Would you like to save the changes to a file? Input 1 for YES and 0 for NO." << "\n";
        int option;
        std::cin >> option;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        if (option == 1)
        {
            saveMaterial(v_mat);
        }

    
}

int searchHU(std::vector <material> v_mat, int targetHU)
{
    for (int i = 0; i < v_mat.size(); i++)
    {
        if(v_mat[i].handling_unit == targetHU)
        {
            return i;
        }
    }
    return -1;
}

int searchMaterial(std::vector <material> v_mat, int targetMaterial)
{
    for (int i = 0; i < v_mat.size(); i++)
    {
        if (v_mat[i].ID_material == targetMaterial)
        {
            return i;
        }
    }
    return -1;
}

int printLocation(material l)
{
    int loc = l.material_location;
    return loc;
}

void saveMaterial(std::vector <material> v_mat)
{
    std::ofstream save_to_file("material.txt");
    if (!save_to_file)
    {
        std::cout << "Unable to open file material.txt\n";
        exit(1);
    }

    int count = 0;
    for (std::vector <material>::iterator it = v_mat.begin(); it != v_mat.end(); it++)
    {
        save_to_file << it->ID_material << ","
                     << it->material_description << ","
                     << it->handling_unit << ","
                     << it->material_location << ",";

        count++;
        if (count != v_mat.size())
        {
            save_to_file << "\n";
        }
    }

    save_to_file.close();

    std::cout << count << " material/s have been successfully added." << "\n\n";
}

int main()
{
    std::vector <material> v_mat;
    ScannerRead(v_mat);
    std::cout << "Total " << v_mat.size() << " records read from the file" << "\n";
    
    printMenu();

    bool quit = false;
    while (!quit)
    {
        std::cout << "Izberi program: \n";
        int option;
        std::cin >> option;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        if (option == 4)
        {
            quit = true;
        }
        else
        {
            doTask(v_mat, option);
        }
    }

    return 0;
}