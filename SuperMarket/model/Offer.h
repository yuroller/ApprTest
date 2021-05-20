#ifndef CPP_OFFER_H
#define CPP_OFFER_H


#include "Product.h"
#include "Discount.h"
#include "SupermarketCatalog.h"
#include "SpecialOfferType.h"
#include <map>

class Offer {
public:
    Offer() = default;
    virtual ~Offer() = default;
    virtual Discount* handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities) = 0;
};

class PercentDiscountOffer : public Offer {
public:
    PercentDiscountOffer(const Product& product, double percentDiscount);
    Discount* handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities) override;
private:
    Product product;
    double percentDiscount;
};

class BuyXQtyPayYQtyOffer : public Offer {
public:
    BuyXQtyPayYQtyOffer(const Product& product, int x, int y);
    Discount* handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities) override;
private:
    Product product;
    int x;
    int y;
};

class BuyXQtyPayAmountOffer : public Offer {
public:
    BuyXQtyPayAmountOffer(const Product& product, int x, double amount);
    Discount* handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities) override;
private:
    Product product;
    int x;
    double amount;
};


#endif //CPP_OFFER_H
