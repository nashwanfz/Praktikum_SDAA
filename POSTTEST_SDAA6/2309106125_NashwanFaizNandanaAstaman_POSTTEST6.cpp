#include <iostream>
#include <iomanip>
#include <cmath> 
using namespace std;

struct senjata
{
    string nama;
    string jenis;
    string jenis_peluru;
    int stok;
    int seri;
    senjata* next;
};

senjata* head = NULL;

void searchWeapon(senjata* head)
{
    if (head == NULL)
    {
        cout << "Tidak ada data senjata." << endl;
        return;
    }

    string searchName;
    cout << "Masukkan nama senjata yang ingin dicari: ";
    fflush(stdin);
    getline(cin, searchName);

    senjata* current = head;
    bool found = false;
    int idx = 1;

    cout << "Hasil pencarian:" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "|No.| Nama Senjata  | Jenis Senjata      |  Jenis Peluru | Stok Senjata | Nomor Seri Senjata |" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;

    while (current != NULL)
    {
        if (current->nama.find(searchName) != string::npos) 
        {
            cout << "[ " << idx << ".] "
                 << setw(14) << left << current->nama << "| "
                 << setw(19) << left << current->jenis << "| "
                 << setw(14) << left << current->jenis_peluru << "| "
                 << setw(13) << left << current->stok << "| "
                 << setw(19) << left << current->seri << "| "
                 << endl;
            found = true;
        }
        current = current->next;
        idx++;
    }

    if (!found)
    {
        cout << "Senjata dengan nama \"" << searchName << "\" tidak ditemukan." << endl;
    }

    cout << "----------------------------------------------------------------------------------------------" << endl;
}

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
    while (current != NULL)
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

void addWeapon(senjata* &head)
{
    system("cls");
    senjata* newNode = new senjata();
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
    newNode->next = head;
    head = newNode;
    cout << "Berhasil menambah data." << endl;
}

void update(senjata* head)
{
    int idx;
    cout << "Masukkan nomor senjata yang ingin diubah: ";
    cin >> idx;

    senjata* current = head;
    for (int i = 1; i < idx && current != NULL; i++)
    {
        current = current->next;
    }

    if (current == NULL)
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

void del(senjata* &head)
{
    int idx;
    cout << "Masukkan nomor senjata yang ingin dihapus: ";
    cin >> idx;

    if (head == NULL)
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
    for (int i = 1; i < idx - 1 && current != NULL; i++)
    {
        current = current->next;
    }

    if (current == NULL || current->next == NULL)
    {
        cout << "Senjata tidak ditemukan." << endl;
        return;
    }

    senjata* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Data senjata berhasil dihapus." << endl;
}

void jumpSearch(senjata* head)
{
    if (!head)
    {
        cout << "Tidak ada data senjata." << endl;
        return;
    }

    int stokTarget;
    cout << "Masukkan stok senjata yang ingin dicari: ";
    cin >> stokTarget;

    senjata* current = head;
    int n = 0;
    while (current != NULL)
    {
        n++;
        current = current->next;
    }

    int step = sqrt(n);
    current = head;

    senjata* prev = NULL;
    int idx = 0;

    while (current != NULL && current->stok < stokTarget)
    {
        prev = current;
        for (int i = 0; i < step && current != NULL; i++)
        {
            current = current->next;
            idx++;
        }
    }

    while (prev != NULL && prev->stok < stokTarget)
    {
        prev = prev->next;
    }

    if (prev != NULL && prev->stok == stokTarget)
    {
        cout << "Senjata ditemukan: " << prev->nama << " dengan stok: " << prev->stok << endl;
    }
    else
    {
        cout << "Senjata dengan stok " << stokTarget << " tidak ditemukan." << endl;
    }
}

void fibonacciSearch(senjata* head)
{
    if (!head)
    {
        cout << "Tidak ada data senjata." << endl;
        return;
    }

    int stokTarget;
    cout << "Masukkan stok senjata yang ingin dicari: ";
    cin >> stokTarget;

    senjata* current = head;
    int n = 0;
    while (current != NULL)
    {
        n++;
        current = current->next;
    }

    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    current = head;

    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);
        senjata* temp = head;

        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }

        if (temp->stok < stokTarget)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->stok > stokTarget)
        {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            cout << "Senjata ditemukan: " << temp->nama << " dengan stok: " << temp->stok << endl;
            return;
        }
    }

    if (fibMMm1 && current->stok == stokTarget)
    {
        cout << "Senjata ditemukan: " << current->nama << " dengan stok: " << current->stok << endl;
    }
    else
    {
        cout << "Senjata dengan stok " << stokTarget << " tidak ditemukan." << endl;
    }
}

int main()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "===================================" << endl;
        cout << "Sistem Manajemen Data Senjata" << endl;
        cout << "===================================" << endl;
        cout << "1. Tambah Senjata" << endl;
        cout << "2. Tampilkan Senjata" << endl;
        cout << "3. Cari Senjata dengan Nama" << endl;
        cout << "4. Cari Senjata dengan Jump Search" << endl;
        cout << "5. Cari Senjata dengan Fibonacci Search" << endl;
        cout << "6. Update Senjata" << endl;
        cout << "7. Hapus Senjata" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
            case 1:
                addWeapon(head);
                break;
            case 2:
                display(head);
                break;
            case 3:
                searchWeapon(head);
                break;
            case 4:
                jumpSearch(head);
                break;
            case 5:
                fibonacciSearch(head);
                break;
            case 6:
                update(head);
                break;
            case 7:
                del(head);
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
        system("pause");
    } while (pilihan != 0);

    return 0;
}
