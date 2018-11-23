#include <iostream>
#include <sstream>

using namespace std;
namespace sequence {
    class BFunction {
        unsigned char *F;
        long size;
    public:
        explicit BFunction(int n) {
            size = 1L << n;
            F = new unsigned char[size];
            for (int i = 0; i < size; ++i) {
                F[i] = 0;
            }
        }

        ~BFunction() {
            delete[]F;
        }

        unsigned char operator()(unsigned long n) {
            return F[n];
        }

        void next() {
            int i = 0;
            for (; i < size && F[i] > 0; ++i) {
                F[i] = 0;
            }
            if (i < size)
                F[i] = 1;
        }

        bool isZero() {
            for (int i = 0; i < size; ++i) {
                if (F[i] > 0)return false;
            }
            return true;
        }

        string toString() {
            stringstream s;
            for (int i = 0; i < size; ++i) {
                s << (int) F[i];
            }
            return s.str();
        }
    };

    ostream &operator<<(ostream &o, BFunction &f) {
        o << f.toString();
        return o;
    }

    void main() {
        int n = 4;
        BFunction f(n);
        int numFound = 0;
        do {
            unsigned long current = 0;
            stringstream s;
            s << f << ": ";
            int i = 0;
            do {
                s << (current & 1);
                current = ((current << 1) | f(current)) & ((1 << n) - 1);
            } while ((current != 0) && (i++ < ((1 << n) + 2)));
            if (current == 0 && i == ((1 << n) - 1)) {
                cout << (++numFound) <<": "<< s.str() << " : " << i << endl;
            }
            f.next();
        } while (!f.isZero());
    }
}

int main(int argc, const char *argv[]) {
    sequence::main();
    return 0;
}
