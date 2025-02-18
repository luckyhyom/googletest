#pragma once  // 중복 포함 방지

class ICatFood {
  public:
    virtual bool IsEmpty() = 0;
    virtual int Burn() = 0;  
};

class CatFood : public ICatFood {
  public:
    virtual bool IsEmpty();
    virtual int Burn();
    CatFood(int energy, int amount);
  private:
    int energy;
    int amount;
};
