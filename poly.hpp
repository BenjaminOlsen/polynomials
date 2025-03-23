#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>

using real = double;

// fwd declaration for polynomial_pair
template <typename T> struct polynomial;

template <typename T>
using polynomial_pair = std::pair<polynomial<T>, polynomial<T>>;

template <typename T>
struct polynomial {

    std::vector<T> coeffs;
    
    polynomial() = default;
    ~polynomial() = default;
    polynomial(const polynomial &other) : coeffs(other.coeffs) {}
    polynomial(std::initializer_list<T> c) : coeffs(c) {}
    polynomial(std::vector<T> c) : coeffs(c) {}
    polynomial(T value): coeffs(1, value) {}
    polynomial(size_t degree, T value): coeffs(degree+1, value) {};

    template <typename... Args>
    polynomial(Args... args) : coeffs{static_cast<T>(args)...} {}

    polynomial& operator*=(const polynomial &other) {
        size_t result_size = coeffs.size() + other.coeffs.size() - 1;
        std::vector<T> result(result_size, 0);
        
        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); j++) {
                result[i+j] += coeffs[i] * other.coeffs[j];
            }    
        }
        coeffs = result;
        return *this;
    }

    void resize(size_t newsize) {
        coeffs.resize(newsize);
    }

    size_t degree() const {
        auto last_nonzero_it = std::find_if(coeffs.rbegin(), coeffs.rend(),
                [](const T& t){ return t != 0; });
        if (last_nonzero_it != coeffs.rend()) {
            return std::distance(coeffs.begin(), last_nonzero_it.base())-1;
        }
        return 0;
    }

    auto begin() {
        return coeffs.begin();
    }

    auto cbegin() const {
        return coeffs.cbegin();
    }

    auto rbegin() {
        return coeffs.rbegin();
    }

    auto cend() const {
        return coeffs.cend();
    }

    auto end() {
        return coeffs.end();
    }

    auto rend() {
        return coeffs.rend(); 
    }

    friend bool operator==(const polynomial &a, const polynomial &b) {
        return !(a != b);
    }

    friend bool operator!=(const polynomial &a, const polynomial &b) {
        size_t sz_a = a.degree();
        size_t sz_b = b.degree();
        if (sz_a != sz_b) {
            return true;
        }
        auto it1 = a.cbegin();
        auto it2 = b.cbegin();
        for(; it1 != a.cend() && it2 != b.cend(); it1++, it2++) {
            if (*it1 != *it2) return true;
        }
        return false;
    }

    T& operator[](size_t idx) {
        return coeffs[idx];
    }

    friend bool operator<(const polynomial &a, const polynomial &b) {
        const size_t deg_a = a.degree();
        const size_t deg_b = b.degree();
        if (deg_a != deg_b) {
            return deg_a < deg_b;
        }
        return a[deg_a] < b[deg_b];
    }


    friend polynomial operator*(const polynomial &a, const polynomial &b) {
        polynomial result(a);
        return result *= b;
    }

    friend polynomial operator*(const T &scalar, const polynomial &poly) {
        polynomial result(poly);
        for (T& val: result.coeffs) {
            val *= scalar;
        }
        return result;
    }

    friend polynomial operator+(const polynomial &a, const polynomial &b) {
        size_t maxSize = std::max(a.coeffs.size(), b.coeffs.size());
        std::vector<T> result(maxSize);
        std::copy_n(a.coeffs.begin(), a.coeffs.size(), result.begin());
        std::transform(result.cbegin(), result.cbegin() + b.coeffs.size(),
                b.coeffs.cbegin(), result.begin(),
                [](const T &a, const T &b){ return a + b; });
        return result;
    }

    const T& operator[](size_t idx) const {
        return coeffs[idx];
    }

    polynomial& operator-=(const polynomial &other) {
        size_t minSize = std::min(coeffs.size(), other.coeffs.size());
        std::transform(coeffs.cbegin(), coeffs.cbegin() + minSize, 
                other.coeffs.cbegin(), coeffs.begin(),
                [](T& a, T& b){ return a - b; });
        return *this;
    }


    void print() const {
        std::cout << *this;
    }

    friend
    polynomial_pair<T> divide(polynomial<T>u, polynomial<T> v) {
        size_t m = u.degree();
        size_t n = v.degree();
        
        printf("................................................");
        printf("dividing \n(deg. %zu) u: ", m); 
        u.print();
        printf(" / \n(deg. %zu) v: ", n);
        v.print();
        polynomial<T> r(std::vector<T>(n+1, 0));
        polynomial<T> q(std::vector<T>(m-n+1, 0));
        for (int k = m - n; k >= 0; --k) {
            q[k] = u[n+k]/v[n];
            std::cout << "q[" << k << "]= u[" << n+k << "]/v[" << n << "]:  " 
                << u[n+k] << "/" << v[n] << " = " << q[k] << "\n"; 
            for (int j = n+k-1; j >= k; --j) {
    //                std::cout << "u["<<j<<"] = u["<<j<<"]-q["<<k<<"]*v["<<j-k<<"]\n";
                u[j] = u[j] - q[k]*v[j-k];
            }        
        }
        std::cout << "q: "; 
        q.print();
        std::cout << "r: ";
        r.print();
        //return r;
        return polynomial_pair<T>(q,r);
    }

    friend std::ostream& operator<<(std::ostream &stream, const polynomial& u) {
        for (int power = static_cast<int>(u.coeffs.size()) - 1; power >= 0; --power) {
            stream << u.coeffs[power] << "x^" << power;
            if (power > 0) {
                stream  << " + ";
            }
        }
        stream << "\n";
        return stream;
    }

};

template <typename T>
polynomial<T> remainder(polynomial<T> u, polynomial<T> v) {
    return polynomial<T>(divide(u,v).second);
}

// stevin's gcd algorithm (1585)
template <typename T>
polynomial<T> gcd(polynomial<T> u, polynomial<T> v) {
    polynomial<T> m{u};
    polynomial<T> n{v};
    while (n != polynomial<T>(0)) {
        polynomial<T> t = remainder(m, n);
        m = n;
        n = t;
    } 
    return m;
}

