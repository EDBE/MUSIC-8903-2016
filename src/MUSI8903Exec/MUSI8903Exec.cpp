
#include <iostream>
#include <ctime>

#include "MUSI8903Config.h"

#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

//    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;

    CAudioFileIf            *phAudioFile        = 0;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    sInputFilePath = "/Users/musictechnology/Desktop/ShortDataset/Bestial_Lust.wav";
    sOutputFilePath = "/Users/musictechnology/Desktop/test1.txt";
    
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::FileIoType_t fileType = CAudioFileIf::kFileRead;
    CAudioFileIf::create(phAudioFile);
    
    phAudioFile -> openFile(sInputFilePath, fileType);
    
    CAudioFileIf::FileSpec_t fileSpec;
    phAudioFile -> getFileSpec(fileSpec);
    int numChannels = fileSpec.iNumChannels;
    
    phAudioFile -> getLength(iInFileLength);
    
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float* [numChannels];
    
    for (int channel = 0; channel < numChannels; channel++) {
        ppfAudioData[channel] = new float [iInFileLength];
    }
    
    // get audio data
    phAudioFile -> readData(ppfAudioData, iInFileLength);
    

    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout
    std::ofstream outfile(sOutputFilePath);
    for (int channel = 0; channel < numChannels; channel++) {
        for (int sample = 0; sample < iInFileLength ; sample++) {
            //            cout << ppfAudioData[channel][sample] << endl;
            //write the data out
            //            outfile.write((char*)&ppfAudioData[channel][sample], sizeof(float));
            outfile <<  ppfAudioData[channel][sample] << endl;
        }
    }
    outfile.close();
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Writing is done!" << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    for (int channel = 0; channel < numChannels; channel++) {
        delete ppfAudioData[channel];
    }
    delete ppfAudioData;
    
    CAudioFileIf::destroy(phAudioFile);
    
    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

