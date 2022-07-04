#include "random.h"

#include <chrono>
#include <array>
#include <string>

using namespace std;

struct CarInfo
{
        string m_manufacturer;
        string m_type;
        string m_origin_time;
};

inline CarInfo GetCarInfo()
{
        constexpr int number_of_manufacturers = 7;
	constexpr int number_of_models_per_manufacturers = 3;
	static pair<string, array<string, number_of_models_per_manufacturers>> car_models[number_of_manufacturers] =
	{
		{"Peugeot", {"308", "208", "3008"}},
		{"Suzuki", {"Swift", "Ignis", "Cross"}},
		{"Honda", {"Civic", "CR-V", "HR-V"}},
		{"Ford", {"Mustang", "Focus", "Ranger"}},
		{"General Motors", {"Hammer H2", "Chevrolet Camaro", "Pontiac Firebird"}},
		{"Renault", {"Clio", "Megan", "Kadjar"}},
		{"Audi", {"A3", "A4", "A6"}}
	};

        auto const cur_time = chrono::system_clock::to_time_t(chrono::system_clock::now());

        int random_manufacturer = RandomInt(0, number_of_manufacturers - 1);
        int random_type = RandomInt(0, number_of_models_per_manufacturers - 1);

        return CarInfo
        {
                car_models[random_manufacturer].first,
                car_models[random_manufacturer].second[random_type],
                ctime(&cur_time)
        };
}
