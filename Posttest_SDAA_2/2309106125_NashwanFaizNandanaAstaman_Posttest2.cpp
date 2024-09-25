#include <iostream> //supaya bisa menggunakan cout dll
#include <iomanip> // supaya bisa menggunakan set w untuk tabel
using namespace std;

struct senjata
{
    string nama;
    string jenis;
    string jenis_peluru;
    int stok;
    int seri;
};

void create(senjata *sjt, int &total) //ada  pointernyat
{
    system("cls"); // membersihkan terminal
    cout << "\n========================\n";
    cout << " Add weapon : " << endl;
    cout << "========================\n";
    cout << "Masukkan nama senjata baru : ";
    fflush(stdin); //untuk menghapus atau flush apalah gituu bang lupa hehe
    getline(cin, sjt->nama);
    cout << "Masukkan Jenis senjata :";
    fflush(stdin);
    getline(cin, sjt->jenis);
    cout << "Masukkan Jenis peluru :";
    fflush(stdin);
    getline(cin, sjt->jenis_peluru);
    while (true)
    {
        cout << "Masukkan Jumlah stok :";
        cin >> sjt->stok;
        if (cin.fail()) //kalau inputan int tpi dimasukkan string maka dia akan membaca ini dan masuk ke error handling
        {
            cin.clear(); // kurang lebih sama
            cin.ignore(); // kurang lebih sama
            cout << "Stoknya harus angka boss " << endl;
            continue;
        }
        break;
    };
    while (true)
    {
        cout << "Masukkan nomor seri dari senjata :";
        cin >> sjt->seri; // karna dia pointer makanya pakai ->
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Nomor seri harus angka boss " << endl;
            continue;
        }
        break;
    };
    total++;
}

void display(senjata *sjt, int total)
{
    fflush(stdin);
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "|No.| Nama Senjata  | Jenis Senjata      |  Jenis Peluru | Stok Senjata | Nomor Seri Senjata |" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < total; i++)
    {
        cout << "[ " << i + 1 << ".] "
             << setw(14) << left << sjt[i].nama << "| "    //set w berfungsi untuk membuat tabel pada display
             << setw(19) << left << sjt[i].jenis << "| "
             << setw(14) << left << sjt[i].jenis_peluru << "| "
             << setw(13) << left << sjt[i].stok << "| "
             << setw(19) << left << sjt[i].seri << "| "
             << endl;
    }
    cout << "----------------------------------------------------------------------------------------------" << endl;
};

void update(senjata *sjt)
{
    cout << "\n========================\n";
    cout << " Add weapon : " << endl;
    cout << "========================\n";
    cout << "Masukkan nama senjata baru : ";
    fflush(stdin);
    getline(cin, sjt->nama);
    cout << "Masukkan Jenis senjata :";
    fflush(stdin);
    getline(cin, sjt->jenis);
    cout << "Masukkan Jenis peluru :";
    fflush(stdin);
    getline(cin, sjt->jenis_peluru);
    while (true)
    {
        cout << "Masukkan Jumlah stok :";
        cin >> sjt->stok;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Stoknya harus angka boss " << endl;
            continue;
        }
        break;
    };
    while (true)
    {
        cout << "Masukkan nomor seri dari senjata :";
        cin >> sjt->seri;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Nomor seri harus angka boss " << endl;
            continue;
        }
        break;
    };
}


int main()
{
    senjata sjt[10];
    int total = 0;
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
        cout << "[4] delete weapon" << endl;
        cout << "[5] exit" << endl;
        cout << "Masukkan pilihan : ";
        cin >> pilih;
        if (pilih == "1")
        {
            create(&sjt[total], total);
            cout << "Berhasil menambah data";
        }
        else if (pilih == "2")
        {
            display(sjt, total);
        }
        else if (pilih == "3")
        {
            display(sjt, total);
            while (true)
            {
                int idx;
                cout << "Mau ubah data ke berapa : ";
                cin >> idx;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Inputan harus berupa angka" << endl;
                    continue;
                }
                else if (idx < 1 || idx > total)
                {
                    cout << "Data tidak ada" << endl;
                    continue;
                }
                update(&sjt[idx - 1]);
                break;
            }
        }
        else if (pilih == "4")
        {
            int hapus;
            while (true)
            {
                display(sjt, total);
                cout << "hapus senjata : ";
                cin >> hapus;
                if (hapus < 1 || hapus > total)
                {
                    cout << "data tidak ada " << endl;
                    break;
                }
                else if(hapus <= total && hapus > 0)
                {

                    for (int i = hapus - 1; i < total; i++)
                    {
                        sjt[i] = sjt[i + 1];
                    }
                    cout << "berhasil hapus data";
                    break;
                }
            }
            total -= 1;
        }
        else if (pilih == "5")
        {
            exit(0);
        }
        else
        {
            cout << "inputan salah";
        }
    }
}