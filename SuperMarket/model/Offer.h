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
    Offer(const SpecialOfferType& offerType, const Product& product, double argument);

    SpecialOfferType getOfferType() const;

    Product getProduct() const;

    double getArgument() const;

    Discount* handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities);

private:
    SpecialOfferType offerType;
    Product product;
    double argument;

};


#endif //CPP_OFFER_H
