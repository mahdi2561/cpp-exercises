//Polynomial.cpp

//private:
void Polynomial::Standardize() {
    sort();
    for (int i = 0; i < MAX_DEGREE && Coefficient[i + 1] != 0; i++) {
        if (degree[i + 1] == degree[i]) {
            Coefficient[i] += Coefficient[i + 1];
            if (i >= MAX_DEGREE)
                break;
            for (int j = i + 1; j < MAX_DEGREE; j++) {
                Coefficient[j] = Coefficient[j + 1];
                degree[j] = degree[j + 1];
            }
            i--;
        }
    }
}
void Polynomial::sort() {
    for (int i = 0; i < MAX_DEGREE; i++) {
        if (Coefficient[i] == 0)
            degree[i] = 0;
        for (int j = i + 1; j <= MAX_DEGREE; j++) {
            if (degree[i] < degree[j]) {
                int temp = degree[i];
                degree[i] = degree[j];
                degree[j] = temp;
                temp = Coefficient[i];
                Coefficient[i] = Coefficient[j];
                Coefficient[j] = temp;
            }
            else  if (degree[i] == degree[j]) {
                Coefficient[i] += Coefficient[j];
                Coefficient[j] = 0;
                degree[j] = 0;
            }
        }
    }
}
//public:
Polynomial::Polynomial() {
    for (int i = 0; i <= MAX_DEGREE; i++) {
        Coefficient[i] = 0;
        degree[i] = 0;
    }
}
Polynomial::Polynomial(const Polynomial& obj) {
    for (int i = 0; i <= MAX_DEGREE; i++) {
        this->Coefficient[i] = obj.Coefficient[i];
        this->degree[i] = obj.degree[i];
    }
}

void Polynomial:: operator=(const Polynomial& obj) {
    for (int i = 0; i <= MAX_DEGREE; i++) {
        this->Coefficient[i] = obj.Coefficient[i];
        this->degree[i] = obj.degree[i];
    }
}

Polynomial Polynomial::operator+(const Polynomial& obj) {
    Polynomial temp, temp2;
    temp = *this;
    temp2 = obj;
    for (int i = 0; i < MAX_DEGREE; i++) {
        for (int j = 0; j < MAX_DEGREE; j++) {
            if (temp.degree[i] == temp2.degree[j]) {
                temp.Coefficient[i] += temp2.Coefficient[j];
                temp2.degree[j] = 0;
                temp2.Coefficient[j] = 0;
            }
        }
    }
    temp2.sort();
    int i = 0;
    for (i = 0; temp.Coefficient[i] != 0; i++);
    for (int j = 0; temp2.Coefficient[j] != 0; j++, i++) {
        temp.Coefficient[i] = temp2.Coefficient[j];
        temp.degree[i] = temp2.degree[j];
    }
    temp.sort();
    return temp;
}
Polynomial Polynomial::operator+(const int var) {
    Polynomial temp = *this;
    bool flag = false;
    int i = 0;
    for (i = 0; temp.Coefficient[i] != 0; i++) {
        if (temp.degree[i] == 0) {
            temp.Coefficient[i] += var;
            flag = true;
        }
    }
    if (!flag)
        temp.Coefficient[i] = var;
    return temp;
}

Polynomial Polynomial::operator-(Polynomial obj) {
    return (*this + (-obj));
}
Polynomial Polynomial::operator-(const int var) {
    Polynomial temp = *this;
    bool flag = false;
    int i = 0;
    for (i = 0; temp.Coefficient[i] != 0; i++) {
        if (temp.degree[i] == 0) {
            temp.Coefficient[i] -= var;
            flag = true;
        }
    }
    if (!flag)
        temp.Coefficient[i] -= var;
    return temp;
}

Polynomial Polynomial::operator*(Polynomial obj) {
    Polynomial temp;
    for (int i = 0, k = 0; this->Coefficient[i] != 0; i++) {
        for (int j = 0; obj.Coefficient[j] != 0; j++, k++) {
            temp.Coefficient[k] = this->Coefficient[i] * obj.Coefficient[j];
            temp.degree[k] = this->degree[i] + obj.degree[j];
            for (int l = 0; l < k; l++) {
                if (temp.degree[k] == temp.degree[l]) {
                    temp.Coefficient[l] += temp.Coefficient[k];
                    k--;
                }
            }
        }
    }
    return temp;
}
Polynomial Polynomial::operator*(const int var) {
    Polynomial temp = *this;
    for (int i = 0; temp.Coefficient[i] != 0; i++) {
        temp.Coefficient[i] *= var;
    }
    return temp;
}

Polynomial& Polynomial::operator++() {
    for (int i = 0; this->Coefficient[i] != 0; i++)
        (this->Coefficient[i])++;
    return *this;
}
Polynomial& Polynomial::operator++(int) {
    Polynomial temp = *this;
    for (int i = 0; this->Coefficient[i] != 0; i++)
        ++(this->Coefficient[i]);
    return temp;
}

Polynomial Polynomial::operator/(Polynomial obj) {
    Polynomial submultiple;
    if (this->degree[0] < obj.degree[0])
        return submultiple;
    else if (this->degree[0] == obj.degree[0] && this->Coefficient[0] < obj.Coefficient[0])
        return submultiple;
    else {
        Polynomial temp = *this, temp2;
        while (temp.degree[0] >= obj.degree[0]) {
            temp2.Coefficient[0] = temp.Coefficient[0] / obj.Coefficient[0];
            temp2.degree[0] = temp.degree[0] - obj.degree[0];
            temp = temp - (temp2 * obj);
            temp.Standardize();
            submultiple = submultiple + temp2;
            submultiple.Standardize();
            if (temp.degree[0] < obj.degree[0])
                return submultiple;
        }
    }
}

Polynomial Polynomial::operator%(Polynomial obj) {
    Polynomial submultiple;
    if (this->degree[0] < obj.degree[0])
        return *this;
    else if (this->degree[0] == obj.degree[0] && this->Coefficient[0] < obj.Coefficient[0])
        return *this;
    else {
        Polynomial temp = *this, temp2;
        while (temp.degree[0] >= obj.degree[0]) {
            temp2.Coefficient[0] = temp.Coefficient[0] / obj.Coefficient[0];
            temp2.degree[0] = temp.degree[0] - obj.degree[0];
            temp = temp - (temp2 * obj);
            temp.Standardize();
            if (temp.degree[0] < obj.degree[0])
                return temp;
        }
    }
}

// friend istream& operator>>(istream&, Polynomial&);
//friend ostream& operator<<(ostream&, const Polynomial&);
istream& operator>>(istream& in, Polynomial& obj) {
    char polynomial[200];
    cin >> polynomial;
    for (int i = 0, j = 0; polynomial[i] != '\0';) {

        if (polynomial[i] == '+')
            i++;

        bool flag = false;

        if (polynomial[i] == '-') {
            flag = true;
            i++;
        }

        if (polynomial[i] == 'x') {
            obj.Coefficient[j] = 1;
            if (flag) {
                obj.Coefficient[j] *= -1;
                flag = false;
            }
            i++;
            if (polynomial[i] != '^') {
                obj.degree[j] = 1;
            }
            else {
                i++;
                char temp[10];
                int k = 0;
                while (polynomial[i] != '+' && polynomial[i] != '-') {
                    if (polynomial[i] == '\0')
                        break;
                    temp[k] = polynomial[i];
                    k++; i++;
                }
                temp[k] = '\0';
                obj.degree[j] = atoi(temp);
                if (polynomial[i] == '\0')
                    break;
            }
            j++;
        }

        else {
            char temp[10];
            int k = 0;
            while (polynomial[i] != 'x') {
                if (polynomial[i] == '\0')
                    break;
                if (polynomial[i] == '+' || polynomial[i] == '-')
                    break;
                temp[k] = polynomial[i];
                k++; i++;
            }
            temp[k] = '\0';
            obj.Coefficient[j] = atoi(temp);
            if (flag) {
                obj.Coefficient[j] *= -1;
                flag = false;
            }
            if (polynomial[i] == '\0')
                break;
            if (polynomial[i] == 'x') {
                i++;
                if (polynomial[i] != '^') {
                    if (obj.Coefficient[j] != 0)
                        obj.degree[j] = 1;
                }
                else if (polynomial[i] == '\0')
                    break;
                else {
                    i++;
                    char temp[10];
                    int k = 0;
                    while (polynomial[i] != '+' && polynomial[i] != '-') {
                        if (polynomial[i] == '\0')
                            break;
                        temp[k] = polynomial[i];
                        k++; i++;
                    }
                    temp[k] = '\0';
                    if (obj.Coefficient[j] != 0)
                        obj.degree[j] = atoi(temp);
                    if (polynomial[i] == '\0')
                        break;
                }
            }
            j++;
        }

    }
    obj.Standardize();
    return in;
}
ostream& operator<<(ostream& out, const Polynomial& obj) {
    for (int i = 0; obj.Coefficient[i] != 0; i++) {
        if (i == 0) {
            if ((obj.Coefficient[0] != 1 && obj.Coefficient[0] != -1) || obj.degree[0] == 0)
                out << obj.Coefficient[0];
            if (obj.degree[0] != 0) {
                out << "x";
                if (obj.degree[0] != 1)
                    out << "^" << obj.degree[0];
            }
            if (obj.Coefficient[0] == 0) {
                out << "0";
                return out;
            }
        }
        else {
            if (obj.Coefficient[i] > 0)
                out << "+";
            if ((obj.Coefficient[i] != 1 && obj.Coefficient[i] != -1) || obj.degree[i] == 0)
                out << obj.Coefficient[i];
            if (obj.degree[i] != 0) {
                if (obj.Coefficient[i] == -1)
                    out << "-";
                out << "x";
                if (obj.degree[i] != 1)
                    out << "^" << obj.degree[i];
            }
        }
    }
    return out;
}

//friend Polynomial operator-(Polynomial obj);
//friend Polynomial operator+(const int var, Polynomial obj);
//friend Polynomial operator-(const int var, Polynomial obj);
//friend Polynomial operator*(const int var, Polynomial obj);
Polynomial operator-(Polynomial obj) {
    for (int i = 0; obj.Coefficient[i] != 0; i++) {
        obj.Coefficient[i] *= -1;
    }
    return obj;
}
Polynomial operator+(const int var, Polynomial obj) {
    bool flag = false;
    int i = 0;
    for (i = 0; obj.Coefficient[i] != 0; i++) {
        if (obj.degree[i] == 0) {
            obj.Coefficient[i] += var;
            flag = true;
        }
    }
    if (!flag)
        obj.Coefficient[i] = var;
    return obj;
}
Polynomial operator-(const int var, Polynomial obj) {
    bool flag = false;
    int i = 0;
    for (i = 0; obj.Coefficient[i] != 0; i++) {
        if (obj.degree[i] == 0) {
            obj.Coefficient[i] -= var;
            flag = true;
        }
    }
    if (!flag)
        obj.Coefficient[i] -= var;
    return obj;
}
Polynomial operator*(const int var, Polynomial obj) {
    for (int i = 0; obj.Coefficient[i] != 0; i++) {
        obj.Coefficient[i] *= var;
    }
    return obj;
}
