#ifndef BARBERSHOP_MANAGER_H_
#define BARBERSHOP_MANAGER_H_

#include <queue>
#include <string>
#include <vector>

class Barber;
class Client;

class BarbershopManager
{
    // 2.	Кожен клас повинен містити 3 загальні та 5 приватні елементи. Відобразити використання усіх полів даних в методах.
    std::vector<Barber*> registered_barbers_;
    std::vector<std::queue<Client*>> client_queues_;
    uint16_t total_orders_accepted_;
    bool is_open_;
    uint16_t max_queue_length_;

    int FindBarberIndex(uint32_t barber_id) const;

public:
    std::string shop_name_;
    uint32_t manager_id_;
    std::string address_;

    BarbershopManager();
    BarbershopManager(const std::string& shop_name, uint32_t manager_id,
        const std::string& address);

    ~BarbershopManager();

    void RegisterBarber(Barber& barber);

    /*
    4.	В кожному класі визначити 6 методів, які опрацьовують описані дані (два методи мають бути перевантаженими),
    де один метод приймає в якості параметрів об’єкт класу, а ще один метод повертає тип класу.
    */
    bool AcceptOrder(Client& client);
    bool AcceptOrder(Client& client, uint32_t barber_id);

    bool ServeNextClient(Barber& barber);

    uint16_t GetQueueLength(uint32_t barber_id) const;

    void DisplayQueues() const;

    Barber GetBusiestBarber() const;


    uint16_t GetTotalOrdersAccepted() const;
    bool IsOpen() const;

    void SetOpen(bool is_open);
};

#endif  // BARBERSHOP_MANAGER_H_
