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
            for (long i = size - 1; i >= 0; --i) {
                s << (int) F[i];
            }
            return s.str();
        }

        unsigned long toNum() {
            unsigned long N = 0;
            for (long i = size - 1; i >= 0; --i) {
                N <<= 1;
                N |= F[i];
            }
            return N;
        }

        string splitToPrimeNumbers() {
            unsigned long n = toNum();
            int div = 2;
            stringstream s;
            bool first = true;
            while (n > 1) {
                while (n % div == 0) {
                    if (!first) {
                        s << " * ";
                    } else {
                        first = false;
                    }
                    s << div;
                    n = n / div;
                }
                div++;
            }
            return s.str();
        }
    };

    ostream &operator<<(ostream &o, BFunction &f) {
        o << f.toString();
        return o;
    }

    void main() {
        int n = 5;
        BFunction f(n);
        int numFound = 0;
        do {
            unsigned long current = 0;
            stringstream s;
            int i = 0;
            do {
                s << (current & 1);
                current = ((current << 1) | f(current)) & ((1 << n) - 1);
            } while ((current != 0) && (i++ < ((1 << n) + 2)));
            if (current == 0 && i == ((1 << n) - 1)) {
                cout << (++numFound) << ": "
                     << f.toNum() << " = "
                     << f.splitToPrimeNumbers() << ": "
                     << f << ": "
                     << s.str() << " : " << i << endl;
            }
            f.next();
        } while (!f.isZero());
    }

}

int main(int argc, const char *argv[]) {
    sequence::main();
    return 0;
}
