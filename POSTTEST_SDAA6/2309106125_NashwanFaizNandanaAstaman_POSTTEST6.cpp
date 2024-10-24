#include <iostream>
#include <iomanip> 
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

void searchWeapon(senjata* head) {
    if (head == NULL) {
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

    while (current != NULL) {
        if (current->nama.find(searchName) != string::npos) {  // Mencari senjata berdasarkan substring
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

    if (!found) {
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

senjata* merge(senjata* left, senjata* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->stok <= right->stok) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

senjata* mergeSort(senjata* head) {
    if (!head || !head->next) return head;

    senjata* slow = head;
    senjata* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    senjata* mid = slow->next;
    slow->next = NULL;

    senjata* left = mergeSort(head);
    senjata* right = mergeSort(mid);

    return merge(left, right);
}

senjata* partition(senjata* head, senjata* end, senjata** newHead, senjata** newEnd) {
    senjata* pivot = end;
    senjata* prev = NULL;
    senjata* cur = head;
    senjata* tail = pivot;

    while (cur != pivot) {
        if (cur->stok > pivot->stok) {
            if (!(*newHead)) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            senjata* temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (!(*newHead)) *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

senjata* quickSortRecur(senjata* head, senjata* end) {
    if (!head || head == end) return head;

    senjata* newHead = NULL;
    senjata* newEnd = NULL;

    senjata* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        senjata* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = NULL;

        newHead = quickSortRecur(newHead, temp);

        senjata* last = newHead;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

senjata* getTail(senjata* cur) {
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

void quickSort(senjata*& head) {
    senjata* tail = getTail(head);  
    head = quickSortRecur(head, tail);  
}

void sortSenjata(senjata*& head) {
    string pilih;
    cout << "Pilih metode sorting:" << endl;
    cout << "[1] Merge Sort (Ascending)" << endl;
    cout << "[2] Quick Sort (Descending)" << endl;
    cout << "Masukkan pilihan : ";
    cin >> pilih;

    if (pilih == "1") {
        head = mergeSort(head);
        cout << "Data senjata berhasil diurutkan secara ascending (stok)." << endl;
    } else if (pilih == "2") {
        quickSort(head);
        cout << "Data senjata berhasil diurutkan secara descending (stok)." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

int main() {
    int pilihan;

    while (true) {
        cout << "\n========================\n";
        cout << "1. Tambah Senjata\n";
        cout << "2. Tampilkan Senjata\n";
        cout << "3. Ubah Senjata\n";
        cout << "4. Hapus Senjata\n";
        cout << "5. Urutkan Senjata\n";
        cout << "6. Search Senjata\n";
        cout << "6. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                addWeapon(head);
                break;
            case 2:
                display(head);
                break;
            case 3:
                update(head);
                break;
            case 4:
                del(head);
                break;
            case 5:
                sortSenjata(head);
                break;
            case 6:
                searchWeapon(head);
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                exit(0);
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }

    return 0;
}