#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- STRUKTUR DATA MLL (One-to-Many) ---

// 1. Child: Data Tamu (Linked List) 
struct NodeTamu {
    string namaTamu;            // Variabel untuk menyimpan Nama Tamu
    string tanggalCheckIn;      // Variabel untuk menyimpan Tanggal Check-in
    NodeTamu* next;             // Pointer 'next'. Menunjuk ke tamu berikutnya dalam satu kamar. 
};

// 2. Parent: Data Kamar (Linked List) 
struct NodeKamar { 
    int nomorKamar;             // Key utama (misal: 101, 102)
    string tipeKamar;           // Data tambahan (misal: "Deluxe")
    long hargaPerMalam;         // Data harga (tipe long untuk angka besar)
    string fasilitas[5];        // Array statis berisi 5 string fasilitas
    
    NodeTamu* tamuHead;     // Pointer Penghubung Parent ke Child (Tamu)
    
    NodeKamar* next;        // Pointer 'next'. Menunjuk ke Kamar berikutnya (misal 101 -> 102). (Linear)
};

// --- PROTOTYPE FUNGSI ---

// Manajemen Kamar (Linked List Parent)
void createKamar(NodeKamar* &head, int nomor, string tipe, long harga); // Insert Sorted
NodeKamar* searchKamar(NodeKamar* head, int nomor); // Linear Search
void deleteKamar(NodeKamar* &head, int nomor); // Delete Linear

// Manajemen Tamu (Linked List Child) 
void checkInTamu(NodeKamar* kamar, string nama, string tanggal); 
void checkOutTamu(NodeKamar* kamar, string nama); 
void viewTamuDiKamar(NodeKamar* kamar); 

// Fitur Pengolahan & Laporan
void viewDenahHotel(NodeKamar* head); // Traversal Linear
void cariTamuGlobal(NodeKamar* head, string namaDicari, bool &found); 
void rekapitulasi(NodeKamar* head, int &totalKamar, long &minHarga, int &maxTamu, int &kamarTerisi); 

// Utility
void initDataDummy(NodeKamar* &head); 

#endif