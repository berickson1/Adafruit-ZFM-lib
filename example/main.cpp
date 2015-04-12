#include <iostream>
#include "../ZFMComm.h"

int main(){
    // initialize reader
    ZFMComm fp = ZFMComm();
    fp.init("/dev/ttyUSB0");

    // remove all fingerprints that are saved on the device to get a fresh start
    fp.deleteAllFingerprints();

    // enter endless loop
    while(1){
        std::cout << "-------------------------" << std::endl;
        std::cout << "First scan" << std::endl;

        // wait until a scan has been successfull
        bool ret = false;
        while(!ret){
            ret = fp.scanFinger();
        }

        // try to find the fingerprint on the device
        int tmp = fp.findFingerprint(1);
        
        if(tmp == -1){ // if finger is not found
            std::cout << "... Did not find fingerprint" << std::endl;
            std::cout << "... will have to scan a second time to add your fingerprint" << std::endl;
            // store the image of the fingerprint to data-buffer 1 ...
            fp.storeImage(1);

            // and scan a second time (needed to create the fingerprint-template)
            std::cout << "Second scan" << std::endl;
            // wait until a scan has been successfull
            bool ret = false;
            while(!ret){
                ret = fp.scanFinger();
            }

            // store the image of the fingerprint to data-buffer 2 ...
            fp.storeImage(2); // store in data-buffer 0

            // ... and finally store the fingerprint with index 12 on the device
            if(fp.storeFingerprint(12)){
                std::cout << "Successfully stored your fingerprint !" << std::endl;
            }
        }else{
            std::cout << "Found finger on index: " << tmp << std::endl;
        }
        std::cout << "----------------------" << std::endl;
    }
}
