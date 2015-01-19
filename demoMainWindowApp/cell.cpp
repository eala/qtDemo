#include "cell.h"

Cell::Cell()
{
    setDirty();
}

QTableWidgetItem *Cell::clone() const{
    return new Cell(*this);
}

void Cell::setFormula(const QString &formula){
    setData(Qt::EditRole, formula);
}

QString Cell::formula() const{
    return data(Qt::EditRole).toString();
}

void Cell::setData(int role, const QVariant &value){
    QTableWidgetItem::setData(role, value);
    if(Qt::EditRole == role)
        setDirty();
}

void Cell::setDirty(){
    cacheIsDirty = true;
}

// QVariant can store different types value, e.g. QString or double
QVariant Cell::data(int role) const{
    if(Qt::DisplayRole == role){
        if(value().isValid()){
            return value().toString();
        }else{
            return "####";
        }
    }else if(Qt::TextAlignmentRole == role){
        if(value().type() == QVariant::String){
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }else{
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    }else{
        return QTableWidgetItem::data(role);
    }
}

const QVariant Invalid;
QVariant Cell::value() const{
    if(cacheIsDirty){
        cacheIsDirty = false;

        QString formulaStr = formula();
        if(formulaStr.startsWith('\'')){    // string start with ', we use \ to escape
            cachedValue = formulaStr.mid(1);
        }else if (formulaStr.startsWith('=')){  // equations
            cachedValue = Invalid;
            QString expr = formulaStr.mid(1);
            expr.replace(" ", "");
            expr.append(QChar::Null);   // for final check end char, if it equals to QChar::Null, it parses successfully

            int pos = 0;
            cachedValue = evalExpression(expr, pos);
            if(expr[pos] != QChar::Null)
                cachedValue = Invalid;
        }else{  // pure numbers or pure strings
            bool ok;
            double d = formulaStr.toDouble(&ok);
            if(ok){
                cachedValue = d;
            }else{
                cachedValue = formulaStr;
            }
        }
    }
    return cachedValue;
}

QVariant Cell::evalExpression(const QString &str, int &pos) const{
    QVariant result = evalTerm(str, pos);
    while(str[pos] != QChar::Null){
        QChar op = str[pos];
        if(op != '+' && op != '-')
            return result;
        ++pos;

        QVariant term = evalTerm(str, pos);
        if(QVariant::Double == result.type()
            && QVariant::Double == term.type()){
            if('+' == op){
                result = result.toDouble() + term.toDouble();
            }else{
                result = result.toDouble() - term.toDouble();
            }
        }else{
            result = Invalid;
        }
    }
    return result;
}

QVariant Cell::evalTerm(const QString &str, int &pos) const{
    QVariant result = evalFactor(str, pos);
    while(QChar::Null != str[pos]){
        QChar op = str[pos];
        if('*' != op && '/' != op)
            return result;
        ++pos;

        QVariant factor = evalFactor(str, pos);
        if(QVariant::Double == result.type()
            && QVariant::Double == factor.type())
        {
            if('*' == op){
                result = result.toDouble() * factor.toDouble();
            }else{
                if(0.0 == factor.toDouble()){
                    result = Invalid;
                }else{
                    result = result.toDouble() / factor.toDouble();
                }
            }
        }else{
            result = Invalid;
        }
    }
    return result;
}

QVariant Cell::evalFactor(const QString &str, int &pos) const{
    QVariant result;
    bool negative = false;

    if('-' == str[pos]){
        negative = true;
        ++pos;
    }

    if('(' == str[pos]){
        ++pos;
        result = evalExpression(str, pos);
        if(')' != str[pos])
            result = Invalid;
        ++pos;
    }else{
        QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
        QString token;

        while(str[pos].isLetterOrNumber() || '.' == str[pos]){
            token += str[pos];
            ++pos;
        }

        if(regExp.exactMatch(token)){
            int column = token[0].toUpper().unicode() - 'A';
            int row = token.mid(1).toInt() - 1;

            Cell *c = static_cast<Cell *>(tableWidget()->item(row, column));
            result = (c)? c->value(): 0.0;
        }else{
            bool ok;
            result = token.toDouble(&ok);
            if(!ok)
                result = Invalid;
        }
    }

    if(negative){
        result = (QVariant::Double == result.type())? result.toDouble() : Invalid;
    }
    return result;
}
