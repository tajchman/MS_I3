/*
 * Matrice.hxx
 *
 */

#ifndef MATRICE_HXX_
#define MATRICE_HXX_

#include <iostream>
#include <string>

class Matrice {
public:
	Matrice(int n=0, int m=0, const char *name = "")
          : m_n(n), m_m(m), m_lignes(new double *[n]), m_coefs(new double [n*m]), m_name(name)
  {
    int i;
    for (i=0; i<n; i++)
       m_lignes[i] = m_coefs + i*m;
  }

  ~Matrice()
  {
    delete [] m_lignes;
    delete [] m_coefs;
  }

  int n() const { return m_n; }
  int m() const { return m_m; }
	inline double operator()(int i,int j) const { return m_lignes[i][j]; }
	inline double & operator()(int i,int j) { return m_lignes[i][j]; }

  const char * name() const { return m_name.c_str(); }

protected:
  int m_n, m_m;
  double * m_coefs;
  double ** m_lignes;
  std::string m_name;
};

std::ostream & operator<<(std::ostream & f, const Matrice & A);

#endif /* MATRICE_HXX_ */
