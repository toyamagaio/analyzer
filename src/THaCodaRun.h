#ifndef ROOT_THaCodaRun
#define ROOT_THaCodaRun

//////////////////////////////////////////////////////////////////////////
//
// THaCodaRun
//
//////////////////////////////////////////////////////////////////////////

#include "THaRunBase.h"
#include "TDatime.h"

class THaCodaData;

class THaCodaRun : public THaRunBase {
  
public:
  THaCodaRun( const char* description="" );
  virtual THaCodaRun& operator=( const THaRunBase& );
  virtual ~THaCodaRun();
  
  virtual Int_t        Close();
  virtual const Int_t* GetEvBuffer() const;
  virtual Bool_t       IsOpen() const;
  virtual Int_t        ReadEvent();

protected:

  THaCodaData*  fCodaData;  //! CODA data associated with this run

  ClassDef(THaCodaRun,1)    // ABC for a run based on CODA data
};


#endif
