#include "Offer.h"

Offer::Offer(const SpecialOfferType& offerType, const Product& product, double argument)
        : offerType(offerType), product(product), argument(argument) {}

SpecialOfferType Offer::getOfferType() const {
        return offerType;
}

Product Offer::getProduct() const {
        return product;
}

double Offer::getArgument() const {
        return argument;
}

Discount* Offer::handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities)
{
    const auto& productQuantity = productQuantities.find(product);
    if (productQuantity == productQuantities.end())
        return nullptr;

    double quantity = productQuantity->second;
    double unitPrice = catalog->getUnitPrice(product);
    int quantityAsInt = (int)quantity;
    Discount* discount = nullptr;
    int x = 1;

    if (offerType == SpecialOfferType::ThreeForTwo) {
        x = 3;
    }
    else if (offerType == SpecialOfferType::TwoForAmount) {
        x = 2;
    } if (offerType == SpecialOfferType::FiveForAmount) {
        x = 5;
    }
    int numberOfXs = quantityAsInt / x;
    if (offerType == SpecialOfferType::ThreeForTwo && quantityAsInt > 2) {
        double discountAmount = quantity * unitPrice - ((numberOfXs * 2 * unitPrice) + quantityAsInt % 3 * unitPrice);
        discount = new Discount("3 for 2", -discountAmount, product);
    }
    if (offerType == SpecialOfferType::TenPercentDiscount) {
        discount = new Discount(std::to_string(argument) + "% off", -quantity * unitPrice * argument / 100.0, product);
    }
    if ((offerType == SpecialOfferType::TwoForAmount || offerType == SpecialOfferType::FiveForAmount)
        && quantityAsInt >= x) {
        double discountTotal = unitPrice * quantity - (argument * numberOfXs + quantityAsInt % x * unitPrice);
        discount = new Discount(std::to_string(x) + " for " + std::to_string(argument), -discountTotal, product);
    }

    return discount;    
}
