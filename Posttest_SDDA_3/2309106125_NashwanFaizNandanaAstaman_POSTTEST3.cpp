#include <iostream>
#include <iomanip> // untuk set w
using namespace std;

struct senjata
{
    string nama;
    string jenis;
    string jenis_peluru;
    int stok;
    int seri;
    senjata* next; // pointer ke node berikutnya dalam linked list
};

senjata* head = nullptr; // pointer ke head linked list

// Fungsi untuk menambahkan senjata ke linked list
void create(senjata* &head)
{
    system("cls"); // membersihkan terminal
    senjata* newNode = new senjata(); // buat node baru
    cout << "\n========================\n";
    cout << " Add weapon : " << endl;
    cout << "========================\n";
    cout << "Masukkan nama senjata baru : ";
    fflush(stdin);
    getline(cin, newNode->nama);
    cout << "Masukkan Jenis senjata :";
    fflush(stdin);
    getline(cin, newNode->jenis);
    cout << "Masukkan Jenis peluru :";
    fflush(stdin);
    getline(cin, newNode->jenis_peluru);
    while (true)
    {
        cout << "Masukkan Jumlah stok :";
        cin >> newNode->stok;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Stoknya harus angka boss " << endl;
            continue;
        }
        break;
    }
    while (true)
    {
        cout << "Masukkan nomor seri dari senjata :";
        cin >> newNode->seri;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Nomor seri harus angka boss " << endl;
            continue;
        }
        break;
    }
    newNode->next = head; // Tambahkan node di depan list
    head = newNode;
    cout << "Berhasil menambah data" << endl;
}

// Fungsi untuk menampilkan senjata di linked list
void display(senjata* head)
{
    senjata* current = head;
    if (!current)
    {
        cout << "Tidak ada data senjata." << endl;
        return;
    }

    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "|No.| Nama Senjata  | Jenis Senjata      |  Jenis Peluru | Stok Senjata | Nomor Seri Senjata |" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;

    int idx = 1;
    while (current != nullptr)
    {
        cout << "[ " << idx << ".] "
             << setw(14) << left << current->nama << "| "
             << setw(19) << left << current->jenis << "| "
             << setw(14) << left << current->jenis_peluru << "| "
             << setw(13) << left << current->stok << "| "
             << setw(19) << left << current->seri << "| "
             << endl;
        current = current->next;
        idx++;
    }
    cout << "----------------------------------------------------------------------------------------------" << endl;
}

// Fungsi untuk memperbarui senjata dalam linked list
void update(senjata* head)
{
    int idx;
    cout << "Masukkan nomor senjata yang ingin diubah: ";
    cin >> idx;
    
    senjata* current = head;
    for (int i = 1; i < idx && current != nullptr; i++)
    {
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Senjata tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan nama senjata baru : ";
    fflush(stdin);
    getline(cin, current->nama);
    cout << "Masukkan Jenis senjata :";
    fflush(stdin);
    getline(cin, current->jenis);
    cout << "Masukkan Jenis peluru :";
    fflush(stdin);
    getline(cin, current->jenis_peluru);
    while (true)
    {
        cout << "Masukkan Jumlah stok :";
        cin >> current->stok;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Stoknya harus angka boss " << endl;
            continue;
        }
        break;
    }
    while (true)
    {
        cout << "Masukkan nomor seri dari senjata :";
        cin >> current->seri;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Nomor seri harus angka boss " << endl;
            continue;
        }
        break;
    }
}

// Fungsi untuk menghapus senjata dari linked list
void del(senjata* &head)
{
    int idx;
    cout << "Masukkan nomor senjata yang ingin dihapus: ";
    cin >> idx;

    if (head == nullptr)
    {
        cout << "Tidak ada data untuk dihapus." << endl;
        return;
    }

    if (idx == 1)
    {
        senjata* temp = head;
        head = head->next;
        delete temp;
        cout << "Data senjata berhasil dihapus." << endl;
        return;
    }

    senjata* current = head;
    for (int i = 1; i < idx - 1 && current != nullptr; i++)
    {
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr)
    {
        cout << "Senjata tidak ditemukan." << endl;
        return;
    }

    senjata* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Data senjata berhasil dihapus." << endl;
}

int main()
{
    string pilih;
    string judul = "Sistem Pendataan Senjata Valorant";

    while (pilih != "5") //membatasi inputan hanya bisa sampai 5
    {
        cout << "\n======================================\n";
        cout << *&judul << endl;
        cout << "======================================\n";
        cout << "List menu:" << endl;
        cout << "[1] Add new weapon" << endl;
        cout << "[2] List weapon" << endl;
        cout << "[3] Update weapon" << endl;
        cout << "[4] Delete weapon" << endl;
        cout << "[5] Exit" << endl;
        cout << "Masukkan pilihan : ";
        cin >> pilih;
        if (pilih == "1")
        {
            create(head);
        }
        else if (pilih == "2")
        {
            display(head);
        }
        else if (pilih == "3")
        {
            display(head);
            update(head);
        }
        else if (pilih == "4")
        {
            display(head);
            del(head);
        }
        else if (pilih == "5")
        {
            exit(0);
        }
        else
        {
            cout << "Inputan salah" << endl;
        }
    }

    return 0;
}