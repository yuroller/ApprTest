#include "ShoppingCart.h"

std::vector<ProductQuantity> ShoppingCart::getItems() const {
    return items;
}

std::map<Product, double> ShoppingCart::getProductQuantities() const {
    return productQuantities;
}

void ShoppingCart::addItem(const Product& product) {
    addItemQuantity(product, 1.0);
}

void ShoppingCart::addItemQuantity(const Product& product, double quantity) {
    items.emplace_back(product, quantity);
    if (productQuantities.find(product) != productQuantities.end()) {
        productQuantities[product] += quantity;
    } else {
        productQuantities[product] = quantity;
    }
}

void ShoppingCart::handleOffers(Receipt& receipt, std::map<Product, Offer> offers, SupermarketCatalog* catalog) {
    for (const auto& productQuantity : productQuantities) {
        Product product = productQuantity.first;
        double quantity = productQuantity.second;
        if (offers.find(product) != offers.end()) {
            auto offer = offers[product];
            double unitPrice = catalog->getUnitPrice(product);
            int quantityAsInt = (int) quantity;
            Discount* discount = nullptr;
            int x = 1;

            if (offer.getOfferType() == SpecialOfferType::ThreeForTwo) {
                x = 3;
            } else if (offer.getOfferType() == SpecialOfferType::TwoForAmount) {
                x = 2;
            } if (offer.getOfferType() == SpecialOfferType::FiveForAmount) {
                x = 5;
            }
            int numberOfXs = quantityAsInt / x;
            if (offer.getOfferType() == SpecialOfferType::ThreeForTwo && quantityAsInt > 2) {
                double discountAmount = quantity * unitPrice - ((numberOfXs * 2 * unitPrice) + quantityAsInt % 3 * unitPrice);
                discount = new Discount("3 for 2", -discountAmount, product);
            }
            if (offer.getOfferType() == SpecialOfferType::TenPercentDiscount) {
                discount = new Discount(std::to_string(offer.getArgument()) + "% off", -quantity * unitPrice * offer.getArgument() / 100.0, product);
            }
            if ((offer.getOfferType() == SpecialOfferType::TwoForAmount || offer.getOfferType() == SpecialOfferType::FiveForAmount)
                && quantityAsInt >= x) {
                double discountTotal = unitPrice * quantity - (offer.getArgument() * numberOfXs + quantityAsInt % x * unitPrice);
                discount = new Discount(std::to_string(x) + " for " + std::to_string(offer.getArgument()), -discountTotal, product);
            }
            if (discount != nullptr)
                receipt.addDiscount(*discount);
        }
    }
}