#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- STRUKTUR DATA MLL (One-to-Many) ---

// 1. Child: Data Tamu (Linked List) 
struct NodeTamu {
    string namaTamu;
    string tanggalCheckIn;
    NodeTamu* next;
};

// 2. Parent: Data Kamar (Linked List) 
struct NodeKamar {
    int nomorKamar;         
    string tipeKamar;       
    long hargaPerMalam;
    string fasilitas[5];    
    
    NodeTamu* tamuHead;     // Pointer ke Child (Tamu)
    
    NodeKamar* next;        // Pointer ke Kamar berikutnya (Linear)
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