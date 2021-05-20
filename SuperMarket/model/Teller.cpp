#include "Teller.h"

Teller::Teller(SupermarketCatalog *catalog) : catalog(catalog) {}

void Teller::addSpecialOffer(SpecialOfferType offerType, const Product& product, double argument) {
    auto offer = [&]() -> Offer* {
        switch (offerType) {
        case SpecialOfferType::ThreeForTwo:
            return new BuyXQtyPayYQtyOffer(product, 3, 2);
        case SpecialOfferType::TenPercentDiscount:
            return new PercentDiscountOffer(product, argument);
        case SpecialOfferType::TwoForAmount:
            return new BuyXQtyPayAmountOffer(product, 2, argument);
        case SpecialOfferType::FiveForAmount:
            return new BuyXQtyPayAmountOffer(product, 5, argument);
        }

        return nullptr;
    }();
    
    if (offer != nullptr)
        offers.emplace(product, offer);
}

Receipt Teller::checksOutArticlesFrom(ShoppingCart theCart) {
    Receipt receipt{};
    std::vector<ProductQuantity> productQuantities = theCart.getItems();
    for (const auto& pq: productQuantities) {
        Product p = pq.getProduct();
        double quantity = pq.getQuantity();
        double unitPrice = catalog->getUnitPrice(p);
        double price = quantity * unitPrice;
        receipt.addProduct(p, quantity, unitPrice, price);
    }
    theCart.handleOffers(receipt, offers, catalog);

    return receipt;
}
