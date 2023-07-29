need :: need()
{

}

need :: need(needType *nType, unsigned int seed)
{
    m_needClass = nType;

    m_value = static_cast<double>(((betterRand(seed * seed + seed)) % 1000))/1000.0f;
    //cout << "setting need value to " << m_value;
    m_currentDropRate = 0;
}

//copy constructor
need :: need(const need& rhs)
{
    m_value = rhs.getValue();
    m_currentDropRate = rhs.getCurrentDropRate();
    m_needClass = rhs.getNeedType();
}

//equals operator
need need :: operator=(const need& rhs)
{
    m_value = rhs.getValue();
    m_currentDropRate = rhs.getCurrentDropRate();
    m_needClass = rhs.getNeedType();

    return *this;
}

//arbitrarily add a number to the need
void need :: add(double amt)
{
    //add the parameter to the value
    m_value += amt;

    //make sure m_value never goes higher than 1
    if (m_value > 1.0f)
    {
        m_value = 1.0f;
    }
}

//arbitrarily subtract a number from the need
void need :: subtract(double amt)
{
    m_value -= amt;

    //make sure m_value never goes lower than 0
    if (m_value < 0)
    {
        m_value = 0;
    }
}

void need :: OnTick()
{
    pawnState test;
}

void need :: setDropRate(double rate)
{
    m_currentDropRate = rate;
}