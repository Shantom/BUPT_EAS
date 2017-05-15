#include "subject.h"

Subject::Subject(QObject *parent) : QObject(parent)
{

}

Subject::Subject(const Subject &src)
{
    long_id=src.long_id;
    short_id=src.short_id;
    name=src.name;
    name_en=src.name_en;
    credit=src.credit;
    property=src.property;
    grade=src.grade;
    reason=src.reason;
}
