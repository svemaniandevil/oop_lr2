#include <algorithm>
#include <iostream>
#include <Windows.h>

#include "Barber.h"
#include "BarbershopManager.h"
#include "Client.h"
#include "Global.h"

uint32_t g_total_appointments = 0;
double g_total_revenue = 0.0;

void PrintRandomArray(const std::string& label, int* array, int size);
void TestBarberFunctionality(Barber& barber_a, Barber& barber_b,
    Client& helper_client);
void TestClientFunctionality(Client& client_a, Client& client_b,
    Barber& helper_barber);
void TestManagerFunctionality(BarbershopManager& manager, Barber& barber_a,
    Barber& barber_b, Client& client_a,
    Client& client_b, Client& client_c);

void InitRandomSeed()
{
    std::srand(static_cast<uint32_t>(std::time(nullptr)));
}

/*
* 12.	Визначити додатковий метод в класі, який виділяє випадкову величину динамічної пам’яті.
* В пам’яті розмістити множину значень одного з цілочисельних полів та відсортувати їх.
*/
int* GenerateSortedRandomArray(int max_value, int* out_size)
{
    int size = kMinRandomArraySize +
        std::rand() % (kMaxRandomArraySize - kMinRandomArraySize + 1);
    int* array = new int[size];
    for (int i = 0; i < size; ++i)
        array[i] = std::rand() % (max_value + 1);
    std::sort(array, array + size);
    *out_size = size;
    return array;
}

void PrintSeparator(const std::string& title)
{
    std::cout << "\n==== " << title << " ====\n" << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    InitRandomSeed();

    PrintSeparator("ПЕРУКАРНЯ");

    // 6.	У програмі побудувати 5 об'єктів, розміщених у статичній пам’яті, а також 5 об’єктів – у динамічній пам'яті.
    Barber barber_static_1("Олена Ковальчук", 1, "жіночі стрижки", 250.0, 4.8, 6);
    Barber barber_static_2("Ігор Петренко", 2, "чоловічі стрижки", 200.0, 4.5, 4);
    Barber barber_static_3("Наталія Бойко", 3, "фарбування", 300.0, 4.9, 8);
    Client client_static_1("Марія Іванова", 101, "+380501112233", 1000.0, 27,
        false);
    Client client_static_2("Андрій Сидоренко", 102, "+380671234567", 500.0, 34,
        false);

    Barber* barber_dynamic_1 =
        new Barber("Тарас Мельник", 4, "укладка", 220.0, 4.6, 5);
    Barber* barber_dynamic_2 =
        new Barber("Софія Гриценко", 5, "масаж голови", 180.0, 4.7, 3);
    Client* client_dynamic_1 =
        new Client("Оксана Лисенко", 103, "+380631112233", 1500.0, 22, false);
    Client* client_dynamic_2 =
        new Client("Роман Захарчук", 104, "+380671112244", 300.0, 45, true);
    Client* client_dynamic_3 =
        new Client("Юлія Кравець", 105, "+380501234567", 2000.0, 30, false);

    // 7.	В основній програмі визначити 2 масиви об'єктів.
    const int kBarberArraySize = 3;
    Barber barber_array[kBarberArraySize] = {
        Barber("Максим Дяченко", 6, "універсал", 210.0, 4.3, 2),
        Barber("Віра Швець", 7, "жіночі стрижки", 260.0, 4.9, 9),
        Barber("Денис Кузьменко", 8, "чоловічі стрижки", 190.0, 4.2, 1) };

    const int kClientArraySize = 3;
    Client client_array[kClientArraySize] = {
        Client("Катерина Мороз", 106, "+380631112222", 800.0, 19, false),
        Client("Богдан Савчук", 107, "+380671113344", 50.0, 52, false),
        Client("Аліна Ткаченко", 108, "+380501113355", 1200.0, 41, true) };

    // 8.	Продемонструвати роботу з об’єктами, розміщеними в даному масиві.
    PrintSeparator("Об'єкти з масивів");
    for (int i = 0; i < kBarberArraySize; ++i) {
        barber_array[i].AddHairstyle("Топ-стрижка");
        barber_array[i].DisplayCatalog();
    }
    for (int i = 0; i < kClientArraySize; ++i)
        client_array[i].DisplayInfo();

    Barber* barber_ptr = &barber_array[0];
    Client* client_ptr = &client_array[2];
    PrintSeparator("Доступ через вказівник на екземпляр класу");
    // 11.	Показати в програмі використання покажчика на екземпляр класу.
    barber_ptr->DisplayCatalog();
    client_ptr->DisplayInfo();



    // 9.	Продемонструвати роботу усіх методів, описаних в класах.
    PrintSeparator("ТЕСТ: функціонал класу Barber");
    TestBarberFunctionality(barber_static_1, barber_static_3, client_static_1);

    PrintSeparator("ТЕСТ: функціонал класу Client");
    TestClientFunctionality(client_static_1, client_static_2, barber_static_2);



    BarbershopManager manager("Перукарня 1", 1,
        "с. , вул. Центральна, 1");
    PrintSeparator("ТЕСТ: функціонал класу BarbershopManager");
    /*
    * 10.	Продемонструвати сценарій взаємодії двох об’єктів
    * (наприклад маємо два класи: студент і книга, тоді необхідно показати, як студент купує книгу).
    */
    TestManagerFunctionality(manager, *barber_dynamic_1, *barber_dynamic_2,
        *client_dynamic_1, *client_dynamic_2,
        *client_dynamic_3);

    delete barber_dynamic_1;
    delete barber_dynamic_2;
    delete client_dynamic_1;
    delete client_dynamic_2;
    delete client_dynamic_3;

    PrintSeparator("ГЛОБАЛЬНА СТАТИСТИКА");
    std::cout << "Всього записів прийнято: "
        << g_total_appointments << std::endl;
    std::cout << "Загальна виручка перукарів: "
        << g_total_revenue << " грн" << std::endl;

    return 0;
}

void PrintRandomArray(const std::string& label, int* array, int size) {
    std::cout << label << " (розмір масиву " << size << "): ";
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void TestBarberFunctionality(Barber& barber_a, Barber& barber_b,
    Client& helper_client) {
    barber_a.AddHairstyle("Каре");
    barber_a.AddHairstyle("Боб-каре");
    barber_a.DisplayCatalog();

    helper_client.BookAppointment(barber_a);
    barber_a.ServeClient(helper_client);

    barber_a.ServeClient(helper_client, "Каре");

    std::cout << "Місячний дохід перукаря " << barber_a.name_ << ": "
        << barber_a.CalculateMonthlyEarnings(30) << " грн" << std::endl;

    Barber best_barber = barber_a.GetBetterBarber(barber_b);
    std::cout << "Кращий перукар (за рейтингом і стажем): " << best_barber.name_
        << std::endl;

    barber_a.SaveToFile("barber_1.txt");
    Barber loaded_barber;
    loaded_barber.LoadFromFile("barber_1.txt");
    std::cout << "Перукар, завантажений з файлу barber_1.txt:" << std::endl;
    loaded_barber.DisplayCatalog();

    int history_size = 0;
    int* experience_history = barber_a.GenerateRandomExperienceHistory(&history_size);
    PrintRandomArray("Відсортована історія стажу перукаря " + barber_a.name_,
        experience_history, history_size);
    delete[] experience_history;
}

void TestClientFunctionality(Client& client_a, Client& client_b,
    Barber& helper_barber) {
    client_a.BookAppointment(helper_barber);
    client_b.BookAppointment(helper_barber, "15:00");

    client_a.PayForService(50.0);
    client_a.UpdateVipStatus();
    client_b.UpdateVipStatus();

    Client older_client = client_a.GetOlderClient(client_b);
    std::cout << "Старший клієнт: " << older_client.name_ << std::endl;

    client_a.DisplayInfo();
    client_b.DisplayInfo();

    client_a.SaveToFile("client_1.txt");
    Client loaded_client;
    loaded_client.LoadFromFile("client_1.txt");
    std::cout << "Клієнт, завантажений з файлу client_1.txt:" << std::endl;
    loaded_client.DisplayInfo();

    int visits_size = 0;
    int* visit_history = client_a.GenerateRandomVisitHistory(&visits_size);
    PrintRandomArray("Відсортована історія візитів клієнта " + client_a.name_,
        visit_history, visits_size);
    delete[] visit_history;
}

void TestManagerFunctionality(BarbershopManager& manager, Barber& barber_a,
    Barber& barber_b, Client& client_a,
    Client& client_b, Client& client_c) {
    manager.RegisterBarber(barber_a);
    manager.RegisterBarber(barber_b);

    manager.AcceptOrder(client_a);

    manager.AcceptOrder(client_b, barber_b.id_);
    manager.AcceptOrder(client_c);

    manager.DisplayQueues();
    std::cout << "Довжина черги до " << barber_a.name_ << ": "
        << manager.GetQueueLength(barber_a.id_) << std::endl;

    manager.ServeNextClient(barber_a);
    manager.ServeNextClient(barber_b);
    manager.ServeNextClient(barber_a);

    manager.DisplayQueues();

    Barber busiest = manager.GetBusiestBarber();
    std::cout << "Найзавантаженіший перукар: " << busiest.name_ << std::endl;
    std::cout << "Всього замовлень прийнято менеджером: "
        << manager.GetTotalOrdersAccepted() << std::endl;
    std::cout << manager.shop_name_
        << " відкрита: " << (manager.IsOpen() ? "так" : "ні")
        << std::endl;

    manager.SetOpen(false);
    std::cout << manager.shop_name_
        << " відкрита: " << (manager.IsOpen() ? "так" : "ні")
        << std::endl;
}
