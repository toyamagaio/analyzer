#ifndef ROOT_THaVhist
#define ROOT_THaVhist

//////////////////////////////////////////////////////////////////////////
//
// THaVhist
//
//////////////////////////////////////////////////////////////////////////

#include "THaString.h"
#include "THaVform.h"
#include "TTree.h"
#include <vector>

class THaVar;
class TH1F;
class TH2F;
class THaCut;

class THaVhist {
  
public:

   THaVhist(THaString type, THaString name, THaString title) : fType(type), fName(name), fTitle(title) { Clear(); }
   virtual ~THaVhist(); 

// Set up the axis and cuts, as applicable.
   void  SetX(Int_t nbinx, Double_t xlo, Double_t xhi, THaString varx);
   void  SetX(THaVform *varx);
   void  SetY(Int_t nbiny, Double_t ylo, Double_t yhi, THaString vary);
   void  SetY(THaVform *vary);
   void  SetCut(THaString cut);
   void  SetCut(THaVform *cut);
   THaString GetVarX() const { return fVarX; };
   THaString GetVarY() const { return fVarY; };
   THaString GetCutStr() const  { return fScut; };
   Int_t CheckCut(Int_t index=0);
   Bool_t HasCut() const { return (fScut != ""); };
   Bool_t IsValid() const { return (fProc == kTRUE); };
// Must Init() once at beginning after various Set()'s
   Int_t Init();
// Must ReAttach() if pointers to global variables reset
   void ReAttach();
// Must Process() each event. 
   Int_t Process();
// Must End() to write histogram to output at end of analysis.
   Int_t End();
// Self-explanatory printouts.
   void  Print() const;
   void  ErrPrint() const;
// CheckValid() checks if this histogram is valid.
// If invalid, you get no output.
   void CheckValidity();
// IsScaler() is kTRUE if histogram is a scaler (which it will then always be)
   Bool_t IsScaler() { return (fScaler==1); };
   Int_t GetSize() { return fSize; };

protected:

   Int_t ParseVar();
   void  Clear();
   Int_t BookHisto(Int_t hfirst, Int_t hlast);
   Int_t FindVarSize();
   Bool_t FindEye(THaString& var);
   Int_t GetCut(Int_t index=0); 

   enum FEr { kOK = 0, kNoBinX, kIllFox, kIllFoy, kIllCut,
              kNoX, kAxiSiz, kCutSix, kCutSiy,
              kUnk };

   static const int fgVERBOSE = 1;
   static const int fgVHIST_HUGE = 10000;

   THaString fType, fName, fTitle, fVarX, fVarY, fScut;
   Int_t fNbinX, fNbinY, fSize, fInitStat, fScaler, fEye;
   Double_t fXlo, fXhi, fYlo, fYhi;
   Bool_t fFirst, fProc;

   std::vector<TH1* > fH1;
   THaVform *fFormX, *fFormY, *fCut;

private:

   THaVhist(const THaVhist& vhist) {}
   THaVhist& operator=(const THaVhist& vhist) { return *this; }

   ClassDef(THaVhist,0)  // Vector of histograms.

};

inline 
void THaVhist::SetX(Int_t nbinx, Double_t xlo, Double_t xhi, THaString varx)
{
  fNbinX = nbinx;  fXlo = xlo;  fXhi = xhi;  fVarX = varx;
};


inline 
void THaVhist::SetX(THaVform *varx)
{
  fFormX = new THaVform("formula", varx->GetName(), varx->GetTitle());
  *fFormX = *varx;
};


inline 
void THaVhist::SetY(Int_t nbiny, Double_t ylo, Double_t yhi, THaString vary)
{
  fNbinY = nbiny;  fYlo = ylo;  fYhi = yhi;  fVarY = vary;
};


inline 
void THaVhist::SetY(THaVform *vary)
{
  fFormY = new THaVform("formula", vary->GetName(), vary->GetTitle());
  *fFormY = *vary;
};


inline 
void THaVhist::SetCut(THaString cut)
{
  fScut = cut;
};


inline 
void THaVhist::SetCut(THaVform *cut)
{
  fCut = new THaVform("cut", cut->GetName(), cut->GetTitle());
  *fCut = *cut;
};

#endif





