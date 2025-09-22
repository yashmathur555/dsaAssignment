// NAME : YASH MATHUR
// ROLL NO. : 2401360020
// COURSE : BTECH CSE(UX/UI)
// SUBJECT : DATA STRUCTURES AND ALGORITHMS LAB
// ASSIGNMENT NO 1. : WEATHER DATA SYSTEM


#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

struct WeatherRecord {
    int year;
    string city;
    double temperature;
};


// Data Storage Class 

class WeatherDataStorage {
private:
    
    vector<vector<double>> weather_data; 
    vector<string> cities;
    int start_year;
    // Sentinel value to represent no data (NaN)
    const double SENTINEL = numeric_limits<double>::quiet_NaN();

public:
    // Constructor initializes the 2D array
    WeatherDataStorage(const vector<string>& city_list, int start_year_val, int num_years)
        : cities(city_list), start_year(start_year_val) {
        // Initialize the 2D vector with SENTINEL values
        weather_data.resize(num_years, vector<double>(cities.size(), SENTINEL));
    }

    // Method to insert a new weather record
    void insert(const WeatherRecord& data) {
        int city_index = -1;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (cities[i] == data.city) {
                city_index = i;
                break;
            }
        }

        int year_index = data.year - start_year;

        // Check if the year and city are within the valid range
        if (city_index != -1 && year_index >= 0 && (size_t)year_index < weather_data.size()) {
            weather_data[year_index][city_index] = data.temperature;
            cout << "Record inserted successfully." << endl;
        } else {
            cout << "Could not insert record. City or year out of range." << endl;
        }
    }

    // Method to delete a weather record based on city and year
    void remove(const string& city, int year) {
        int city_index = -1;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (cities[i] == city) {
                city_index = i;
                break;
            }
        }
        
        int year_index = year - start_year;

        if (city_index != -1 && year_index >= 0 && (size_t)year_index < weather_data.size()) {
            // Check if there is data to delete
            if (!isnan(weather_data[year_index][city_index])) {
                weather_data[year_index][city_index] = SENTINEL;
                cout << "Record deleted successfully." << endl;
            } else {
                cout << "No record found to delete for the specified city and year." << endl;
            }
        } else {
            cout << "Could not delete record. City or year out of range." << endl;
        }
    }

    // Method to retrieve temperature data for a specific city and year
    void retrieve(const string& city, int year) {
        int city_index = -1;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (cities[i] == city) {
                city_index = i;
                break;
            }
        }

        int year_index = year - start_year;

        if (city_index != -1 && year_index >= 0 && (size_t)year_index < weather_data.size()) {
            double temp = weather_data[year_index][city_index];
            if (!isnan(temp)) {
                cout << "Temperature in " << city << " in " << year << " was " << temp << "°C." << endl;
            } else {
                cout << "No data available for " << city << " in " << year << "." << endl;
            }
        } else {
            cout << "Invalid city or year." << endl;
        }
    }

    // Method to display data using row-major access (Year -> City)
    void rowMajorAccess() {
        cout << "\n--- Row-Major Access ---" << endl;
        bool found_data = false;
        // Outer loop iterates over rows (years)
        for (size_t year_idx = 0; year_idx < weather_data.size(); ++year_idx) {
            // Inner loop iterates over columns (cities)
            for (size_t city_idx = 0; city_idx < cities.size(); ++city_idx) {
                double temp = weather_data[year_idx][city_idx];
                if (!isnan(temp)) {
                    cout << "Year: " << (start_year + year_idx) << ", City: " << cities[city_idx] << ", Temp: " << temp << "°C" << endl;
                    found_data = true;
                }
            }
        }
        if (!found_data) {
            cout << "No data to display." << endl;
        }
    }

    // Method to display data using column-major access (City -> Year)
    void columnMajorAccess() {
        cout << "\n--- Column-Major Access ---" << endl;
        bool found_data = false;
        // Outer loop iterates over columns (cities)
        for (size_t city_idx = 0; city_idx < cities.size(); ++city_idx) {
            // Inner loop iterates over rows (years)
            for (size_t year_idx = 0; year_idx < weather_data.size(); ++year_idx) {
                double temp = weather_data[year_idx][city_idx];
                if (!isnan(temp)) {
                    cout << "City: " << cities[city_idx] << ", Year: " << (start_year + year_idx) << ", Temp: " << temp << "°C" << endl;
                    found_data = true;
                }
            }
        }
        if (!found_data) {
            cout << "No data to display." << endl;
        }
    }
};



// Main function 


int main() {
    // list of cities
    vector<string> city_list = {"Delhi", "Mumbai", "Kolkata", "Chennai", "Bengaluru", "Hyderabad", "Pune", "Ahmedabad"};
    
    // capacity for 15 years starting from 2010
    WeatherDataStorage data_system(city_list, 2011, 15); 

    int choice;
    do {
        cout << "\nWeather Data Storage System\n";
        cout << "1. Insert a record\n";
        cout << "2. Delete a record\n";
        cout << "3. Retrieve a record\n";
        cout << "4. Display data (Row-Major)\n";
        cout << "5. Display data (Column-Major)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Basic input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // Set to an invalid choice
        }

        switch (choice) {
            case 1: {
                WeatherRecord rec;
                cout << "Enter year: ";
                cin >> rec.year;
                cout << "Enter city: ";
                cin >> rec.city;
                cout << "Enter temperature: ";
                cin >> rec.temperature;
                data_system.insert(rec);
                break;
            }
            case 2: {
                string city;
                int year;
                cout << "Enter city to delete: ";
                cin >> city;
                cout << "Enter year to delete: ";
                cin >> year;
                data_system.remove(city, year);
                break;
            }
            case 3: {
                string city;
                int year;
                cout << "Enter city to retrieve: ";
                cin >> city;
                cout << "Enter year to retrieve: ";
                cin >> year;
                data_system.retrieve(city, year);
                break;
            }
            case 4:
                data_system.rowMajorAccess();
                break;
            case 5:
                data_system.columnMajorAccess();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}

