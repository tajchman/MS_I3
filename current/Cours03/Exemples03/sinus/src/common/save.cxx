#include "save.hxx"
#include <fstream>

void save(const char *name,
	  std::vector<double> & pos,
	  std::vector<double> & v1,
	  std::vector<double> & v2)
{
  std::string resultName = name;
  resultName += ".dat";
  std::ofstream f(resultName.c_str());

  f  << "# x sin(systeme) approximation" << std::endl;
  int i, n = pos.size();
  for (i=0; i<n; i++)
    f << pos[i] << " " << v1[i] << " " << v2[i] << std::endl;
  
  std::string s = name;
  s += ".gnp";
  std::ofstream t(s.c_str());
  t << "set output '" << name << ".pdf'\n"
    << "set term pdf\n"
    << "plot '" << resultName << "' using 1:2 notitle w l lw 3, '"
                << resultName << "' using ($1):($3+0.03) notitle w l lw 3";
  
  t << std::endl;
}

