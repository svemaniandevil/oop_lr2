#ifndef BARBER_H_
#define BARBER_H_

#include <string>
#include <vector>

class Client;

// 1.	Визначити 2 будь-яких користувацьких класи, обраних з варіанта завдань (не менше 8 полів на клас).
class Barber
{
    // 2.	Кожен клас повинен містити 3 загальні та 5 приватні елементи. Відобразити використання усіх полів даних в методах.
    double price_per_cut_;
    double rating_;
    uint8_t experience_years_;
    std::vector<std::string> hairstyle_catalog_;
    uint16_t served_clients_count_;

public:
    uint32_t id_;
    std::string name_;
    std::string specialization_;

    Barber();
    Barber(const std::string& name, uint32_t id,
        const std::string& specialization, double price_per_cut, double rating,
        uint8_t experience_years);

    ~Barber();


    void AddHairstyle(const std::string& style);

    void DisplayCatalog() const;

    /*
    * 4.	В кожному класі визначити 6 методів, які опрацьовують описані дані (два методи мають бути перевантаженими),
    * де один метод приймає в якості параметрів об’єкт класу, а ще один метод повертає тип класу.
    */
    void ServeClient(Client& client);
    void ServeClient(Client& client, const std::string& chosen_style);

    double CalculateMonthlyEarnings(uint8_t days_worked) const;

    Barber GetBetterBarber(const Barber& other) const;


    // 5.	Визначити в класі методи для запису у файл та читання з файлу полів даних.
    void SaveToFile(const std::string& filename) const;

    void LoadFromFile(const std::string& filename);


    int* GenerateRandomExperienceHistory(int* out_size) const;

    double GetPricePerCut() const;
    double GetRating() const;
    uint8_t GetExperienceYears() const;
    uint16_t GetServedClientsCount() const;

    bool SetPricePerCut(double price_per_cut);
    bool SetRating(double rating);
};

#endif  // BARBER_H_
