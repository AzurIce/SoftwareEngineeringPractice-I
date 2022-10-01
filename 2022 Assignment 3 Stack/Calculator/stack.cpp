/**
 * An implementation of Stack structure based on class template.
 *
 * Author: AzurIce(XiaoBin)
 * Date: 2022-09-30
 *
 **/
#include "stack.h"

template<>
QString Stack<double>::toString() {
   QString s = "[";
   for (int i = 0; i < _size; i++) {
       s.append(QString::number(_stack[i]));
       if (i != _size - 1) s.append(", ");
   }
   return s;
}
