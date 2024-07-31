#include <iostream>
#include <iomanip>
using namespace std;

class TemperatureConverter {
public:
    double celsiusToFahrenheit(double celsius) {
        return (celsius * 9.0 / 5.0) + 32.0;
    }
    double fahrenheitToCelsius(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }

    double celsiusToKelvin(double celsius) {
        return celsius + 273.15;
    }
    double kelvinToCelsius(double kelvin) {
        return kelvin - 273.15;
    }
    double fahrenheitToKelvin(double fahrenheit) {
        return celsiusToKelvin(fahrenheitToCelsius(fahrenheit));
    }
    double kelvinToFahrenheit(double kelvin) {
        return celsiusToFahrenheit(kelvinToCelsius(kelvin));
    }
};

void showMenu() {
    cout << "Temperature Conversion Program" <<endl;
    cout << "1. Celsius to Fahrenheit" <<endl;
    cout << "2. Fahrenheit to Celsius" <<endl;
    cout << "3. Celsius to Kelvin" <<endl;
    cout << "4. Kelvin to Celsius" <<endl;
    cout << "5. Fahrenheit to Kelvin" <<endl;
    cout << "6. Kelvin to Fahrenheit" <<endl;
    cout << "7. Exit" <<endl;
}

int main() {
    TemperatureConverter converter;
    int choice;
    double temperature, result;

    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) {
            cout << "Exiting program." <<endl;
            break;
        }

        cout << "Enter the temperature: ";
        cin >> temperature;

        switch (choice) {
            case 1:
                result = converter.celsiusToFahrenheit(temperature);
                cout <<fixed << setprecision(2)
                          << temperature << " Celsius is " << result << " Fahrenheit" <<endl;
                break;
            case 2:
                result = converter.fahrenheitToCelsius(temperature);
                cout <<fixed << setprecision(2)
                          << temperature << " Fahrenheit is " << result << " Celsius" <<endl;
                break;
            case 3:
                result = converter.celsiusToKelvin(temperature);
                cout << fixed << setprecision(2)
                          << temperature << " Celsius is " << result << " Kelvin" <<endl;
                break;
            case 4:
                result = converter.kelvinToCelsius(temperature);
                std::cout << std::fixed << std::setprecision(2)
                          << temperature << " Kelvin is " << result << " Celsius" << std::endl;
                break;
            case 5:
                result = converter.fahrenheitToKelvin(temperature);
                cout << fixed <<setprecision(2)
                          << temperature << " Fahrenheit is " << result << " Kelvin" <<endl;
                break;
            case 6:
                result = converter.kelvinToFahrenheit(temperature);
                cout <<fixed << setprecision(2)
                          << temperature << " Kelvin is " << result << " Fahrenheit" <<endl;
                break;
            default:
                cout << "Invalid choice. Please try again." <<endl;
        }

        cout <<endl;
    }

    return 0;
}
