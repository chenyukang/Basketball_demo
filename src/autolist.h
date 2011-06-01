#ifndef AUTOLIST_H
#define AUTOLIST_H


#include <list>

template <class T>
class AutoList
{
public:

  typedef std::list<T*> ObjectList;
  
private:

  static ObjectList m_Members;

protected:

  AutoList()
  {
    //cast this object to type T* and add it to the list
    m_Members.push_back(static_cast<T*>(this));
  }

  ~AutoList()
  {
    m_Members.remove(static_cast<T*>(this));    
  }

public:


  static ObjectList& GetAllMembers(){return m_Members;}
};


template <class T>
std::list<T*> AutoList<T>::m_Members;



#endif
