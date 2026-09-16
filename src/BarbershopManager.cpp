#include "BarbershopManager.h"

#include <iostream>

#include "Barber.h"
#include "Client.h"
#include "Global.h"

BarbershopManager::BarbershopManager()
    : shop_name_("Перукарня без назви"),
    manager_id_(0),
    address_("(не вказано)"),
    total_orders_accepted_(0),
    is_open_(true),
    max_queue_length_(kDefaultMaxQueueLength)
{
}

BarbershopManager::BarbershopManager(const std::string& shop_name,
    uint32_t manager_id,
    const std::string& address)
    : shop_name_(shop_name),
    manager_id_(manager_id),
    address_(address),
    total_orders_accepted_(0),
    is_open_(true),
    max_queue_length_(kDefaultMaxQueueLength)
{
}

BarbershopManager::~BarbershopManager()
{
    registered_barbers_.clear();
    client_queues_.clear();
}


void BarbershopManager::RegisterBarber(Barber& barber)
{
    registered_barbers_.push_back(&barber);
    client_queues_.emplace_back();
    std::cout << shop_name_ << ": зареєстровано перукаря " << barber.name_
        << std::endl;
}

int BarbershopManager::FindBarberIndex(uint32_t barber_id) const
{
    for (size_t i = 0; i < registered_barbers_.size(); ++i)
        if (registered_barbers_[i]->id_ == barber_id)
            return (int)i;
    return -1;
}

bool BarbershopManager::AcceptOrder(Client& client)
{
    if (registered_barbers_.empty())
        return false;
    size_t best_index = 0;
    for (size_t i = 1; i < client_queues_.size(); ++i)
        if (client_queues_[i].size() < client_queues_[best_index].size())
            best_index = i;
    client_queues_[best_index].push(&client);
    ++total_orders_accepted_;
    ++g_total_appointments;
    std::cout << client.name_ << " доданий(-а) у чергу до перукаря "
        << registered_barbers_[best_index]->name_ << std::endl;
    return true;
}

bool BarbershopManager::AcceptOrder(Client& client, uint32_t barber_id)
{
    int index = FindBarberIndex(barber_id);
    if (index == -1) {
        std::cout << "Перукаря з ID " << barber_id << " не знайдено." << std::endl;
        return false;
    }
    client_queues_[index].push(&client);
    ++total_orders_accepted_;
    ++g_total_appointments;
    std::cout << client.name_ << " доданий(-а) у чергу до перукаря "
        << registered_barbers_[index]->name_ << std::endl;
    return true;
}

bool BarbershopManager::ServeNextClient(Barber& barber)
{
    int index = FindBarberIndex(barber.id_);
    if (index == -1 || client_queues_[index].empty())
        return false;
    Client* next_client = client_queues_[index].front();
    client_queues_[index].pop();
    barber.ServeClient(*next_client);
    return true;
}

uint16_t BarbershopManager::GetQueueLength(uint32_t barber_id) const
{
    int index = FindBarberIndex(barber_id);
    if (index == -1)
        return -1;
    return static_cast<uint16_t>(client_queues_[index].size());
}

void BarbershopManager::DisplayQueues() const
{
    std::cout << shop_name_ << " (" << address_ << ") -- стан черг:"
        << std::endl;
    for (size_t i = 0; i < registered_barbers_.size(); ++i)
        std::cout << "  " << registered_barbers_[i]->name_ << ": "
            << client_queues_[i].size() << " клієнт(ів) у черзі"
            << std::endl;
}

Barber BarbershopManager::GetBusiestBarber() const
{
    if (registered_barbers_.empty())
        return Barber();
    const Barber* busiest = registered_barbers_.front();
    for (const Barber* barber : registered_barbers_)
        if (barber->GetServedClientsCount() > busiest->GetServedClientsCount())
            busiest = barber;
    return *busiest;
}

uint16_t BarbershopManager::GetTotalOrdersAccepted() const
{
    return total_orders_accepted_;
}

bool BarbershopManager::IsOpen() const { return is_open_; }
void BarbershopManager::SetOpen(bool is_open) { is_open_ = is_open; }
