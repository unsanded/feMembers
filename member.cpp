#include "member.h"

Member::Member(QObject *parent) :
  QObject(parent),
  dateJoined(QDate::currentDate()),
  currentlyMember(true)
{
}


Member::Member(const Member &other):
  firstName(other.firstName),
  lastName(other.lastName),
  street(other.street),
  houseNumber(other.houseNumber),
  postalCode(other.postalCode),
  city(other.city),
  country(other.country),
  nationality(other.nationality),
  email(other.email),
  studentNumber(other.studentNumber),
  gender(other.gender),
  initials(other.initials),
  sportscardNumber(other.sportscardNumber),
  phoneNumber(other.phoneNumber),
  comments(other.comments),
  birthDate(other.birthDate),
  dateJoined(other.dateJoined),
  dateLeft(other.dateLeft),
  currentlyMember(other.currentlyMember)
{
}
Member::Member(Member &other):
  firstName(other.firstName),
  lastName(other.lastName),
  street(other.street),
  houseNumber(other.houseNumber),
  postalCode(other.postalCode),
  city(other.city),
  country(other.country),
  nationality(other.nationality),
  email(other.email),
  studentNumber(other.studentNumber),
  gender(other.gender),
  initials(other.initials),
  sportscardNumber(other.sportscardNumber),
  phoneNumber(other.phoneNumber),
  comments(other.comments),
  birthDate(other.birthDate),
  dateJoined(other.dateJoined),
  dateLeft(other.dateLeft),
  currentlyMember(other.currentlyMember)
{
}
