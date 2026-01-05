#include "hotel.h"

int main() {
 
    NodeKamar* head = NULL; 
    
    initDataDummy(head); 

    int pilihan;
    do {
        cout << "\n======================================\n";
        cout << "    SISTEM RESERVASI TILEM SUITES     \n";
        cout << "======================================\n";
        cout << "1. Lihat Denah Hotel & Status Kamar\n";
        cout << "2. Check-In Tamu Baru\n";
        cout << "3. Cari Tamu (by Nama)\n";
        cout << "4. Pindah Kamar\n";
        cout << "5. Edit Nama Tamu\n";
        cout << "6. Check-Out Tamu\n";
        cout << "7. REKAPITULASI (Total & Statistik)\n";
        cout << "8. Keluar\n";
        cout << "======================================\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch(pilihan) {
            case 1: {
                cout << "\n--- DENAH HOTEL ---\n";
                viewDenahHotel(head);
                break;
            }
            case 2: {
                int noKamar;
                string nama, tgl;
                cout << "Masukkan No Kamar: "; cin >> noKamar;
                NodeKamar* k = searchKamar(head, noKamar); // Linear Search
                if (k) {
                    cin.ignore(); 
                    cout << "Nama Tamu: "; getline(cin, nama);
                    cout << "Tanggal Check-In: "; getline(cin, tgl);
                    checkInTamu(k, nama, tgl);
                } else {
                    cout << "Kamar tidak ditemukan!\n";
                }
                break;
            }
            case 3: {
                string cari;
                bool found = false;
                cin.ignore();
                cout << "Masukkan Nama Tamu: "; getline(cin, cari);
                cout << "\n--- HASIL PENCARIAN ---\n";
                cariTamuGlobal(head, cari, found);
                if (!found) cout << "Tamu tidak ditemukan di kamar manapun.\n";
                break;
            }
            case 4: {
                int lama, baru;
                string nama, tgl;
                cout << "Nomor Kamar Lama: "; cin >> lama;
                cout << "Nomor Kamar Baru: "; cin >> baru;
                
                NodeKamar* kLama = searchKamar(head, lama);
                NodeKamar* kBaru = searchKamar(head, baru);
                
                if (kLama && kBaru) {
                    cin.ignore();
                    cout << "Nama Tamu yg Pindah: "; getline(cin, nama);
                    cout << "Tanggal Check-In Baru: "; getline(cin, tgl);
                    
                    checkOutTamu(kLama, nama); 
                    checkInTamu(kBaru, nama, tgl);
                    cout << "Proses pindah kamar selesai.\n";
                } else {
                    cout << "Salah satu nomor kamar tidak valid.\n";
                }
                break;
            }
            case 5: {
                int no;
                string namaLama, namaBaru;
                cout << "No Kamar Tamu: "; cin >> no;
                NodeKamar* k = searchKamar(head, no);
                if(k) {
                    cin.ignore();
                    cout << "Nama Lama: "; getline(cin, namaLama);
                    
                    NodeTamu* t = k->tamuHead;
                    bool ketemu = false;
                    while(t){
                        if(t->namaTamu == namaLama){
                            cout << "Nama Baru: "; getline(cin, namaBaru);
                            t->namaTamu = namaBaru;
                            cout << "Nama berhasil diubah.\n";
                            ketemu = true;
                            break;
                        }
                        t = t->next;
                    }
                    if(!ketemu) cout << "Tamu tidak ditemukan.\n";
                }
                break;
            }
            case 6: {
                int no;
                string nama;
                cout << "Masukkan No Kamar: "; cin >> no;
                NodeKamar* k = searchKamar(head, no);
                if (k) {
                    cin.ignore();
                    cout << "Nama Tamu Check-Out: "; getline(cin, nama);
                    checkOutTamu(k, nama);
                } else {
                    cout << "Kamar tidak valid.\n";
                }
                break;
            }
            case 7: {
                int totKamar = 0, maxTamu = 0, terisi = 0;
                long minHarga = 999999999;
                
                rekapitulasi(head, totKamar, minHarga, maxTamu, terisi);
                
                cout << "\n--- REKAPITULASI HOTEL ---\n";
                cout << "Total Kamar: " << totKamar << endl;
                cout << "Kamar Terisi: " << terisi << endl;
                cout << "Harga Termurah: Rp" << (totKamar > 0 ? minHarga : 0) << endl;
                cout << "Rekor Tamu Terbanyak: " << maxTamu << " orang\n";
                break;
            }
            case 8:
                cout << "Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 8);

    return 0;
}