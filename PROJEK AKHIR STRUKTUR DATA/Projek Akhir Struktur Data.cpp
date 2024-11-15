#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int stock;
    Product* next;
};

struct CartItem {
    int id;
    string name;
    double price;
    int quantity;
    CartItem* next;
};

struct User {
    string username;
    string password;
};



// Fungsi untuk menampilkan produk
void displayProducts(Product* head) {
    cout << "Daftar Produk:\n";
    Product* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id << ", Nama: " << current->name
             << ", Harga: " << current->price << ", Stok: " << current->stock << endl;
        current = current->next;
    }
}

// Fungsi untuk menambahkan produk dengan validasi input
void addProduct(Product*& head) {
    Product* newProduct = new Product;

    // Validasi untuk ID
    do {
        cout << "Masukkan ID Produk: ";
        cin >> newProduct->id;
        if (newProduct->id <= 0) {
            cout << "ID tidak boleh negatif atau nol. Silakan coba lagi.\n";
        }
    } while (newProduct->id <= 0);

    cout << "Masukkan Nama Produk: ";
    cin.ignore(); 
    getline(cin, newProduct->name);

    // Validasi untuk Harga
    do {
        cout << "Masukkan Harga Produk: ";
        cin >> newProduct->price;
        if (newProduct->price < 0) {
            cout << "Harga tidak boleh negatif. Silakan coba lagi.\n";
        }
    } while (newProduct->price < 0);

    // Validasi untuk Stok
    do {
        cout << "Masukkan Stok Produk: ";
        cin >> newProduct->stock;
        if (newProduct->stock <= 0) {
            cout << "Stok harus lebih dari 0. Silakan coba lagi.\n";
        }
    } while (newProduct->stock <= 0);

    newProduct->next = head;
    head = newProduct;
    cout << "Produk berhasil ditambahkan.\n";
}

// Fungsi untuk menghapus produk berdasarkan ID
void deleteProduct(Product*& head, int id) {
    Product* current = head;
    Product* prev = nullptr;

    while (current != nullptr && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << "Produk berhasil dihapus.\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Fungsi untuk mengedit produk dengan validasi input
void editProduct(Product* head, int id) {
    Product* current = head;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }
    if (current != nullptr) {
        cout << "Edit Nama Produk: ";
        cin.ignore(); 
        getline(cin, current->name);

        // Validasi untuk Harga
        do {
            cout << "Edit Harga Produk: ";
            cin >> current->price;
            if (current->price < 0) {
                cout << "Harga tidak boleh negatif. Silakan coba lagi.\n";
            }
        } while (current->price < 0);

        // Validasi untuk Stok
        do {
            cout << "Edit Stok Produk: ";
            cin >> current->stock;
            if (current->stock < 0) {
                cout << "Stok tidak boleh negatif. Silakan coba lagi.\n";
            }
        } while (current->stock < 0);

        cout << "Produk berhasil diperbarui.\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Fungsi untuk menampilkan produk dalam keranjang
void displayCart(CartItem* cart) {
    if (cart == nullptr) {
        cout << "Keranjang kosong.\n";
        return;
    }

    cout << "Keranjang Belanja:\n";
    CartItem* current = cart;
    double total = 0.0;
    while (current != nullptr) {
        cout << "ID: " << current->id 
             << ", Nama: " << current->name 
             << ", Harga: " << current->price 
             << ", Jumlah: " << current->quantity << endl; // Show quantity in cart
        total += current->price * current->quantity;
        current = current->next;
    }
    cout << "Total Harga: " << total << endl;
}

// Fungsi untuk menambahkan produk ke keranjang berdasarkan ID
void addToCart(Product*& products, CartItem*& cart, int id, int quantity) {
    Product* current = products;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }

    if (current != nullptr && current->stock >= quantity) { // Check if product exists and has stock
        // Create a new cart item
        CartItem* newCartItem = new CartItem;
        newCartItem->id = current->id;
        newCartItem->name = current->name;
        newCartItem->price = current->price;
        newCartItem->quantity = quantity; // User-defined quantity
        newCartItem->next = nullptr;

        // Decrement stock from product list
        current->stock -= quantity;

        // Add the cart item to the cart
        if (cart == nullptr) {
            cart = newCartItem;
        } else {
            CartItem* temp = cart;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newCartItem;
        }

        cout << "Produk berhasil ditambahkan ke keranjang.\n";
    } else {
        cout << (current == nullptr ? "Produk tidak ditemukan.\n" : "Stok tidak cukup.\n");
    }
}

// Fungsi untuk login
bool login(User& user, User users[], int userCount) {
    cout << "Enter Username: ";
    cin >> user.username;
    cout << "Enter Password: ";
    cin >> user.password;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == user.username && users[i].password == user.password) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk registrasi user baru
void registerUser(User users[], int& userCount) {
    User newUser;
    cout << "Enter Username: ";
    cin >> newUser.username;
    cout << "Enter Password: ";
    cin >> newUser.password;
    users[userCount++] = newUser;
    cout << "Registration successful. You can now login.\n";
}

// Fungsi Search berdasarkan nama (Boyer-Moore)
int boyerMooreSearch(Product* head, const string& keyword) {
    Product* current = head;
    int position = 0;

    while (current != nullptr) {
        int m = keyword.size();
        int n = current->name.size();
        int badChar[256];

        // Inisialisasi tabel karakter buruk
        for (int i = 0; i < 256; i++) {
            badChar[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            badChar[(int)keyword[i]] = i;
        }

        // Lakukan pencarian Boyer-Moore
        int shift = 0;
        while (shift <= (n - m)) {
            int j = m - 1;

            // Cek kecocokan
            while (j >= 0 && keyword[j] == current->name[shift + j]) {
                j--;
            }

            if (j < 0) {
                cout << "Produk ditemukan: ID: " << current->id << ", Nama: " << current->name
                     << ", Harga: " << current->price << ", Stok: " << current->stock << endl;
                return position;
            } else {
                shift += max(1, j - badChar[(int)current->name[shift + j]]);
            }
        }

        current = current->next;
        position++;
    }

    cout << "Produk dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
    return -1;
}

// Fungsi Search berdasarkan ID (Fibonacci Search)
Product* fibonacciSearch(Product* head, int id) {
    vector<Product*> sortedProducts;
    Product* current = head;

    // Buat array terurut berdasarkan ID
    while (current != nullptr) {
        sortedProducts.push_back(current);
        current = current->next;
    }
    sort(sortedProducts.begin(), sortedProducts.end(),
         [](Product* a, Product* b) { return a->id < b->id; });

    int n = sortedProducts.size();
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    // Fibonacci angka berikutnya
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    // Cari berdasarkan Fibonacci
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (sortedProducts[i]->id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (sortedProducts[i]->id > id) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << "Produk ditemukan: ID: " << sortedProducts[i]->id
                 << ", Nama: " << sortedProducts[i]->name
                 << ", Harga: " << sortedProducts[i]->price
                 << ", Stok: " << sortedProducts[i]->stock << endl;
            return sortedProducts[i];
        }
    }

    if (fibMMm1 && offset + 1 < n && sortedProducts[offset + 1]->id == id) {
        cout << "Produk ditemukan: ID: " << sortedProducts[offset + 1]->id
             << ", Nama: " << sortedProducts[offset + 1]->name
             << ", Harga: " << sortedProducts[offset + 1]->price
             << ", Stok: " << sortedProducts[offset + 1]->stock << endl;
        return sortedProducts[offset + 1];
    }

    cout << "Produk dengan ID " << id << " tidak ditemukan.\n";
    return nullptr;
}

// Fungsi Search berdasarkan harga (Jump Search)
Product* jumpSearch(Product* head, double price) {
    vector<Product*> sortedProducts;
    Product* current = head;

    // Buat array terurut berdasarkan harga
    while (current != nullptr) {
        sortedProducts.push_back(current);
        current = current->next;
    }
    sort(sortedProducts.begin(), sortedProducts.end(),
         [](Product* a, Product* b) { return a->price < b->price; });

    int n = sortedProducts.size();
    int step = sqrt(n);
    int prev = 0;

    // Lompat-lompat
    while (sortedProducts[min(step, n) - 1]->price < price) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Produk dengan harga " << price << " tidak ditemukan.\n";
            return nullptr;
        }
    }

    // Linear Search di blok yang ditemukan
    for (int i = prev; i < min(step, n); i++) {
        if (sortedProducts[i]->price == price) {
            cout << "Produk ditemukan: ID: " << sortedProducts[i]->id
                 << ", Nama: " << sortedProducts[i]->name
                 << ", Harga: " << sortedProducts[i]->price
                 << ", Stok: " << sortedProducts[i]->stock << endl;
            return sortedProducts[i];
        }
    }

    cout << "Produk dengan harga " << price << " tidak ditemukan.\n";
    return nullptr;
}



int main() {
    Product* products = nullptr;
    CartItem* cart = nullptr;
    User users[100];
    int userCount = 0;
    User currentUser;
    bool isAdmin = false;

    // Menambahkan user Admin default
    users[userCount++] = {"Admin", "Admin123"};

    int choice;

    // Loop utama program
    while (true) {
        cout << "\n1. Login\n2. Register\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (login(currentUser, users, userCount)) {
                isAdmin = (currentUser.username == "Admin" && currentUser.password == "Admin123");
                cout << (isAdmin ? "Logged in as Admin.\n" : "Logged in as Guest.\n");

                // Menu Admin atau Guest
                while (true) {
                    if (isAdmin) {
                        cout << "\nAdmin Menu:\n";
                        cout << "1. Display Products\n2. Add Product\n3. Edit Product\n4. Delete Product\n5. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        if (choice == 1) {
                            displayProducts(products);
                        } else if (choice == 2) {
                            addProduct(products);
                        } else if (choice == 3) {
                            int id;
                            cout << "Enter Product ID to edit: ";
                            cin >> id;
                            editProduct(products, id);
                        } else if (choice == 4) {
                            int id;
                            cout << "Enter Product ID to delete: ";
                            cin >> id;
                            deleteProduct(products, id);
                        } else if (choice == 5) {
                            break;
                        }
                    } else {
                        cout << "\nGuest Menu:\n";
                        cout << "1. Display Products\n2. Add to Cart\n3. View Cart\n4. Search Produk\n5. Logout";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        if (choice == 1) {
                            displayProducts(products);
                        } else if (choice == 2) {
                            int id, quantity;
                            cout << "Enter Product ID to add to cart: ";
                            cin >> id;
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            addToCart(products, cart, id, quantity);
                        } else if (choice == 3) {
                            displayCart(cart);
                        } else if (choice == 4) {
                    int searchChoice;
                    cout << "\nSearch Methods:\n";
                    cout << "1. Search by Name (Boyer-Moore)\n";
                    cout << "2. Search by Price (Jump Search)\n";
                    cout << "3. Search by ID (Fibonacci Search)\n";
                    cout << "Enter your choice: ";
                    cin >> searchChoice;

                    if (searchChoice == 1) {
                        string keyword;
                        cout << "Enter product name keyword: ";
                        cin.ignore();
                        getline(cin, keyword);
                        boyerMooreSearch(products, keyword);
                    } else if (searchChoice == 2) {
                        double price;
                        cout << "Enter product price: ";
                        cin >> price;
                        jumpSearch(products, price);
                    } else if (searchChoice == 3) {
                        int id;
                        cout << "Enter product ID: ";
                        cin >> id;
                        fibonacciSearch(products, id);
                    } else {
                        cout << "Invalid search choice.\n";
                    }
                }
                        else if (choice == 5) {
                            break;
                        }
                    }
                }
            } else {
                cout << "Invalid login.\n";
            }
        } else if (choice == 2) {
            registerUser(users, userCount);
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}