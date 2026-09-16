#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>

class Barber;

// 1.	Визначити 2 будь-яких користувацьких класи, обраних з варіанта завдань (не менше 8 полів на клас).
class Client
{
    // 2.	Кожен клас повинен містити 3 загальні та 5 приватні елементи. Відобразити використання усіх полів даних в методах.
    double balance_;
    uint8_t age_;
    uint16_t visit_count_;
    bool is_vip_;
    // 3.	Забезпечити зв'язок двох об’єктів шляхом розміщення об’єкта одного класу в іншому без використання дружніх функцій.
    Barber* assigned_barber_;

public:
    uint32_t id_;
    std::string name_;
    std::string phone_;

    Client();
    Client(const std::string& name, uint32_t id, const std::string& phone,
        double balance, uint8_t age, bool is_vip);

    ~Client();


    /*
    * 4.	В кожному класі визначити 6 методів, які опрацьовують описані дані (два методи мають бути перевантаженими),
    * де один метод приймає в якості параметрів об’єкт класу, а ще один метод повертає тип класу.
    */
    void BookAppointment(Barber& barber);
    void BookAppointment(Barber& barber, const std::string& preferred_time);

    bool PayForService(double amount);

    void UpdateVipStatus();

    Client GetOlderClient(const Client& other) const;

    void DisplayInfo() const;


    // 5.	Визначити в класі методи для запису у файл та читання з файлу полів даних.
    void SaveToFile(const std::string& filename) const;

    void LoadFromFile(const std::string& filename);


    int* GenerateRandomVisitHistory(int* out_size) const;


    double GetBalance() const;
    uint8_t GetAge() const;
    uint16_t GetVisitCount() const;
    bool IsVip() const;
    Barber* GetAssignedBarber() const;
};

#endif  // CLIENT_H_
