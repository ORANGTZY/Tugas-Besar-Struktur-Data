#include "hotel.h"

// --- IMPLEMENTASI PARENT (KAMAR) - MLL ---

void createKamar(NodeKamar* &head, int nomor, string tipe, long harga) {
    // Buat Node Baru
    NodeKamar* baru = new NodeKamar;
    baru->nomorKamar = nomor;               // Mengisi nomor kamar.
    baru->tipeKamar = tipe;                 // Mengisi tipe kamar.
    baru->hargaPerMalam = harga;            // Mengisi harga.
    baru->tamuHead = NULL;                  
    baru->next = NULL;                      
    
    // Default Fasilitas 
    // Mengisi array fasilitas satu per satu secara manual
    baru->fasilitas[0] = "WiFi";
    baru->fasilitas[1] = "AC";
    baru->fasilitas[2] = "TV";
    baru->fasilitas[3] = "Air Panas";
    baru->fasilitas[4] = "Sarapan";

    // INSERT SORTED (Agar kamar tersusun rapi dari nomor kecil ke besar)
    
    // Case 0: List kosong atau nomor baru lebih kecil dari head
    if (head == NULL || nomor < head->nomorKamar) {
        baru->next = head;                                         // Sambungkan node baru ke head lama.
        head = baru;                                               // Pindahkan label 'head' ke node baru. 
        cout << "Kamar " << nomor << " berhasil dibangun.\n";
        return;
    }

    // Cek duplikasi di Head
    if (head->nomorKamar == nomor) {                                 // Jika nomor kamar sama persis dengan head.
        cout << "Error: Nomor kamar " << nomor << " sudah ada!\n";
        delete baru;                                                 // Batalkan pembuatan node (hapus dari memori). 
        return;
    }

    // Traversal untuk mencari posisi yang pas
    NodeKamar* temp = head;                                             // Buat pointer bantuan 'temp' di awal.
    while (temp->next != NULL && temp->next->nomorKamar < nomor) {      
        temp = temp->next;                                              // Maju satu langkah.
    }

    // Cek duplikasi di tengah/akhir
    if (temp->nomorKamar == nomor || (temp->next != NULL && temp->next->nomorKamar == nomor)) {
        cout << "Error: Nomor kamar " << nomor << " sudah ada!\n";
        delete baru;
    } else {
        // Sisipkan node
        baru->next = temp->next;
        temp->next = baru;
        cout << "Kamar " << nomor << " berhasil dibangun.\n";
    }
}

NodeKamar* searchKamar(NodeKamar* head, int nomor) {
    // Linear Search O(N)
    NodeKamar* temp = head;                                 // Mulai dari depan.
    while (temp != NULL) {                                  // Selama belum sampai ujung (NULL).
        if (temp->nomorKamar == nomor) {                    
            return temp;                                    // Ketemu, Kembalikan alamat memorinya.
        }
        temp = temp->next;                                  // Pindah ke node berikutnya.
    }
    return NULL;                                            // Tidak ketemu sampai habis.
}

void deleteKamar(NodeKamar* &head, int nomor) {
    if (head == NULL) return;

    // Case 1: Hapus Head
    if (head->nomorKamar == nomor) {
        // Hapus semua tamu dulu (Child)
        while (head->tamuHead != NULL) {
            NodeTamu* t = head->tamuHead;
            head->tamuHead = head->tamuHead->next;
            delete t;
        }
        
        NodeKamar* hapus = head;
        head = head->next;
        delete hapus;
        cout << "Kamar berhasil dihapus.\n";
        return;
    }

    // Case 2: Hapus di tengah/akhir
    NodeKamar* temp = head;
    NodeKamar* prev = NULL;
    
    while (temp != NULL && temp->nomorKamar != nomor) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Kamar tidak ditemukan.\n";
    } else {
        // Kamar ketemu, hapus tamunya dulu
        while (temp->tamuHead != NULL) {
            NodeTamu* t = temp->tamuHead;
            temp->tamuHead = temp->tamuHead->next;
            delete t;
        }

        // Relinking pointer parent
        prev->next = temp->next;
        delete temp;
        cout << "Kamar berhasil dihapus.\n";
    }
}

// --- IMPLEMENTASI CHILD (TAMU) --- 

void checkInTamu(NodeKamar* kamar, string nama, string tanggal) {
    // --- LOGIKA PENGECEKAN (VALIDASI) ---
    
    // Cek apakah ada tamu di dalam kamar (Head child tidak NULL)
    if (kamar->tamuHead != NULL) {
        cout << "FAILED: Kamar " << kamar->nomorKamar 
             << " sedang TERISI oleh tamu '" << kamar->tamuHead->namaTamu 
             << "'.\nHarap lakukan Check-Out terlebih dahulu!\n";
        return; // Hentikan proses, tidak boleh lanjut check-in
    }

    // --- JIKA KOSONG, LANJUT PROSES CHECK-IN ---

    NodeTamu* baru = new NodeTamu;
    baru->namaTamu = nama;
    baru->tanggalCheckIn = tanggal;
    baru->next = NULL;

    // Karena sudah dipastikan kosong (dari if diatas), 
    // kita bisa langsung pasang sebagai Head tanpa perlu traversing ke belakang.
    kamar->tamuHead = baru;

    cout << "Check-in BERHASIL untuk " << nama << " di kamar " << kamar->nomorKamar << endl;
}

void checkOutTamu(NodeKamar* kamar, string nama) {
    if (kamar->tamuHead == NULL) {
        cout << "Tidak ada tamu di kamar ini.\n";
        return;
    }

    NodeTamu* temp = kamar->tamuHead;
    NodeTamu* prev = NULL;

    while (temp != NULL && temp->namaTamu != nama) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Tamu atas nama " << nama << " tidak ditemukan.\n";
        return;
    }

    if (prev == NULL) {
        kamar->tamuHead = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Check-out berhasil untuk " << nama << ".\n";
}

void viewTamuDiKamar(NodeKamar* kamar) {
    cout << "   Daftar Tamu: ";
    NodeTamu* t = kamar->tamuHead;
    if (t == NULL) {
        cout << "[Kosong]";
    } else {
        while (t != NULL) {
            cout << t->namaTamu << "(" << t->tanggalCheckIn << ") -> ";
            t = t->next;
        }
        cout << "NULL";
    }
    cout << endl;
}

// --- FUNGSI TAMPILAN & PENGOLAHAN (Traversal Linear) ---

void viewDenahHotel(NodeKamar* head) {
    NodeKamar* temp = head;
    while (temp != NULL) {
        cout << "--------------------------------\n";
        cout << "No Kamar: " << temp->nomorKamar 
             << " | Tipe: " << temp->tipeKamar 
             << " | Harga: Rp" << temp->hargaPerMalam << endl;
        viewTamuDiKamar(temp); // Panggil fungsi child
        temp = temp->next;
    }
    if (head == NULL) cout << "Belum ada kamar yang dibangun.\n";
}

void cariTamuGlobal(NodeKamar* head, string namaDicari, bool &found) {
    NodeKamar* k = head;
    while (k != NULL) {
        // Cek child di setiap kamar
        NodeTamu* t = k->tamuHead;
        while (t != NULL) {
            if (t->namaTamu == namaDicari) {
                cout << "- Ditemukan di Kamar " << k->nomorKamar 
                     << " (Tgl: " << t->tanggalCheckIn << ")\n";
                found = true;
            }
            t = t->next;
        }
        k = k->next;
    }
}

void rekapitulasi(NodeKamar* head, int &totalKamar, long &minHarga, int &maxTamu, int &kamarTerisi) {
    NodeKamar* temp = head;
    while (temp != NULL) {
        totalKamar++;
        if (temp->hargaPerMalam < minHarga) minHarga = temp->hargaPerMalam;
        
        int countTamu = 0;
        NodeTamu* t = temp->tamuHead;
        while (t != NULL) {
            countTamu++;
            t = t->next;
        }
        
        if (countTamu > 0) kamarTerisi++;
        if (countTamu > maxTamu) maxTamu = countTamu;
        
        temp = temp->next;
    }
}

void initDataDummy(NodeKamar* &head) {
    createKamar(head, 101, "Standard", 500000);
    createKamar(head, 102, "Standard", 500000);
    createKamar(head, 201, "Deluxe", 800000);
    createKamar(head, 301, "Suite", 1500000);
    
    NodeKamar* k = searchKamar(head, 101);
    if(k) checkInTamu(k, "Budi", "01-12-2025");
    if(k) checkInTamu(k, "Andi", "05-12-2025");
    
    k = searchKamar(head, 301);
    if(k) checkInTamu(k, "Sultan", "01-12-2025");
}