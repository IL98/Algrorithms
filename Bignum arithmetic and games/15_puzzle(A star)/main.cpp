#include <sstream>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <sstream>
#include <string>
#include <set>
#include <queue>

using namespace std;




class CPosition {
public:
    explicit CPosition( const std::string& source );
    string path;

    CPosition Up() const;
    CPosition Down() const;
    CPosition Left() const;
    CPosition Right() const;
    unsigned short Manhattan() const;
    unsigned char getAt( int place ) const;
    unsigned long long data; // 16 ячеек по 4 бита каждая.
    int Size;
    int nullPlace;
private:
    void setAt( int place, unsigned char value );
};

const unsigned long long Masks[] = {
        0x000000000000000F,
        0x00000000000000F0,
        0x0000000000000F00,
        0x000000000000F000,
        0x00000000000F0000,
        0x0000000000F00000,
        0x000000000F000000,
        0x00000000F0000000,
        0x0000000F00000000,
        0x000000F000000000,
        0x00000F0000000000,
        0x0000F00000000000,
        0x000F000000000000,
        0x00F0000000000000,
        0x0F00000000000000,
        0xF000000000000000,
};

const unsigned long long AntiMasks[] = {
        0xFFFFFFFFFFFFFFF0,
        0xFFFFFFFFFFFFFF0F,
        0xFFFFFFFFFFFFF0FF,
        0xFFFFFFFFFFFF0FFF,
        0xFFFFFFFFFFF0FFFF,
        0xFFFFFFFFFF0FFFFF,
        0xFFFFFFFFF0FFFFFF,
        0xFFFFFFFF0FFFFFFF,
        0xFFFFFFF0FFFFFFFF,
        0xFFFFFF0FFFFFFFFF,
        0xFFFFF0FFFFFFFFFF,
        0xFFFF0FFFFFFFFFFF,
        0xFFF0FFFFFFFFFFFF,
        0xFF0FFFFFFFFFFFFF,
        0xF0FFFFFFFFFFFFFF,
        0x0FFFFFFFFFFFFFFF
};

class Compar
{
public:
    bool operator()(CPosition & a, CPosition & b)
    {
        return ((a.Manhattan() + a.Size) > b.Manhattan() + b.Size);
    }
};

int proverka(string s)
{
    CPosition g(s);
    int v = 0;
    for (int i(0); i < 16; i++)
    {
        if (i != g.nullPlace)
        {
            int n = g.getAt(i);
            for (int j(0); j < i; j++)
            {
                if (g.getAt(j) > n)
                    ++v;
            }
        }
    }
    v += g.nullPlace/4 + 1;
    return v;
}

string A_star(string s)
{
    CPosition base(s);
    priority_queue <CPosition, vector<CPosition>, Compar> q;
    set <unsigned  long long int> Used;
    q.push(base);
    while (!q.empty())
    {
        CPosition p = q.top();
        if (p.data == 1147797409030816545)
          return p.path;
        q.pop();
        Used.insert(p.data);
        int def = p.nullPlace / 4;
        int mod = p.nullPlace % 4;
        if (def)
        {
            if (Used.find(p.Up().data) == Used.end())
            {
                if (p.Up().data == 1147797409030816545)
                    return p.path + "D";
                CPosition u = p.Up();
                q.push(u);
            }

        }
        if (def != 3)
        {
            if (Used.find(p.Down().data) == Used.end())
            {
                if (p.Down().data == 1147797409030816545)
                    return p.path + "U";
                CPosition d = p.Down();
                q.push(d);
            }
        }
        if (mod)
        {
            if (Used.find(p.Left().data) == Used.end())
            {
                if (p.Left().data == 1147797409030816545)
                    return p.path + "R";
                CPosition l = p.Left();
                q.push(l);
            }
        }
        if (mod != 3)
        {
            if (Used.find(p.Right().data) == Used.end())
            {
                if (p.Right().data == 1147797409030816545)
                    return p.path + "L";
                CPosition u = p.Right();
                q.push(u);
            }
        }

    }
    return "w";
}



int main(int argc, char* argv[])
{
    string s;
    for (char i(0); i <16; i++){
        string m;
        cin >> m;
        s += " ";
        s += m;
    }

    if (proverka(s) & 1)
        cout << -1;
    else{
        string v = A_star(s);
        cout << v.length() << endl;
        cout << v;
    }


    return 0;
}


unsigned short CPosition ::Manhattan() const
{
    unsigned short s = 0;
    for (char i(0); i < 4; i++)
        for (char j(0); j < 4; j++)
        {
           if (nullPlace != i * 4 + j)
           {
               char n = getAt(i * 4 + j);
               char x = (n - 1) % 4 ;
               char y = (n - 1)/ 4;
               s += abs(x - j) + abs(y - i);
           }else{
               s += abs(3 - j) + abs(3 - i);
           }

        }

    return s;
}


CPosition::CPosition( const std::string& source ) :
        data( 0 ),
        nullPlace( 0 ),
        Size(0)
{
    std::istringstream stringStream( source );
    for( char i = 0; i < 16; ++i ) {
        unsigned short value = 0;
        stringStream >> value;
        setAt( i, static_cast<unsigned char>( value ) );
        if( value == 0 ) {
            nullPlace = i;
        }
    }
    path = "";
}

// Установка значения в некоторую позицию.
void CPosition::setAt( int place, unsigned char value )
{
    data = ( data & AntiMasks[place] ) | ( static_cast<long long>( value ) << ( place << 2 ) );
}

// Получение того, что лежит в некоторой позиции.
unsigned char CPosition::getAt( int place ) const
{
    return static_cast<unsigned char>( ( data & Masks[place] ) >> ( place << 2 ) );
}

CPosition CPosition::Up() const
{
    assert( nullPlace >= 4 );

    CPosition result( *this );

    // Ставим пустышку выше.
    result.setAt( nullPlace - 4, 0 );
    // Ставим то, что было выше, на то место, где была пустышка.
    result.setAt( nullPlace, getAt( nullPlace - 4 ) );
    result.nullPlace -= 4;
    result.Size++;
    result.path += "D";
    return result;
}

CPosition CPosition ::Left() const
{
    CPosition result (*this);
    //что было ставим туда где пустышка
    result.setAt(nullPlace, getAt(nullPlace - 1));
    //сдвигаем пустышку влево
    result.setAt(nullPlace - 1, 0);
    result.nullPlace -= 1;
    result.Size++;
    result.path += "R";
    return result;
}

CPosition CPosition ::Down() const
{
    assert(nullPlace <= 11);
    CPosition result( *this );
    result.setAt( nullPlace + 4, 0);
    result.setAt(nullPlace, getAt(nullPlace + 4));
    result.nullPlace += 4;
    result.Size++;
    result.path += "U";
    return result;
}

CPosition CPosition ::Right() const
{
    CPosition result (*this);
    result.setAt(nullPlace, getAt(nullPlace + 1));
    result.setAt(nullPlace + 1, 0);
    result.nullPlace += 1;
    result.Size++;
    result.path += "L";
    return result;
}
