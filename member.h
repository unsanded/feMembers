#ifndef MEMBER_H
#define MEMBER_H

#include <QDate>
#include <QObject>

class Member : public QObject
{
  Q_OBJECT
public:
  Member(Member& other);
  Member(const Member& other);

  explicit Member(QObject *parent = 0);
  QString
        firstName,
        lastName,
        street,
        houseNumber,
        postalCode,
        city,
        country,
        nationality,
        email,
        studentNumber,
        gender,
        initials,
        sportscardNumber,
        phoneNumber,
        comments;
  QDate birthDate;
  QDate dateJoined;
  QDate dateLeft;
  bool currentlyMember;

signals:

public slots:

};

#endif // MEMBER_H
