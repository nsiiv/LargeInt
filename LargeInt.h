
#include <iostream>
#include <vector>

namespace bigint {

    class LargeInt {
    public:
        LargeInt();
        LargeInt(std::string num);          
        LargeInt(uint32_t num);

        bool operator>(const LargeInt& rhs) const;
        bool operator<(const LargeInt& rhs) const;
        bool operator==(const LargeInt& rhs) const;

        const LargeInt operator+(const LargeInt& rhs) const;
        const LargeInt operator-(const LargeInt& rhs) const;
        const LargeInt operator*(const LargeInt& rhs) const;
        const LargeInt operator/(const LargeInt& rhs) const;

        std::string num_to_str() const;                         
        LargeInt abs() const;                                   

    private:
        std::vector<uint32_t> number;
        bool sign;                     

        void deleteZero();                                     
        LargeInt digitMultiply(uint32_t digit) const;          
        int digit(int index) const;                            
    };

   std::ostream& operator <<(std::ostream& ostream, const LargeInt& number);
}
