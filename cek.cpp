    switch (col) {
      case 1:
        if (order == 1) {
          rule1 = sorted->data.ID_barang >= newnode->data.ID_barang;
        } else {
          rule1 = sorted->data.ID_barang <= newnode->data.ID_barang;
        }
        break;
      case 2:
        if (order == 1) {
          rule1 = sorted->data.nama >= newnode->data.nama;
        } else {
          rule1 = sorted->data.nama <= newnode->data.nama;
        }
        break;
      case 3:
        if (order == 1) {
          rule1 = sorted->data.harga >= newnode->data.harga;
        } else {
          rule1 = sorted->data.harga <= newnode->data.harga;
        }
        break;
      case 4:
        if (order == 1) {
          rule1 = sorted->data.stock >= newnode->data.stock;
        } else {
          rule1 = sorted->data.stock <= newnode->data.stock;
        }
        break;
      case 5:
        if (order == 1) {
          rule1 = sorted->data.tExpired >= newnode->data.tExpired;
        } else {
          rule1 = sorted->data.tExpired <= newnode->data.tExpired;
        }
        break;
    }



      switch (col) {
        case 1:
          if (order == 1) {
            rule2 = current->next->data.ID_barang < newnode->data.ID_barang;
          } else {
            rule2 = current->next->data.ID_barang > newnode->data.ID_barang;
          }
        case 2:
          if (order == 1) {
            rule2 = current->next->data.nama < newnode->data.nama;
          } else {
            rule2 = current->next->data.nama > newnode->data.nama;
          }
          break;
        case 3:
          if (order == 1) {
            rule2 = current->next->data.harga < newnode->data.harga;
          } else {
            rule2 = current->next->data.harga > newnode->data.harga;
          }
          break;
        case 4:
          if (order == 1) {
            rule2 = current->next->data.stock < newnode->data.stock;
          } else {
            rule2 = current->next->data.stock > newnode->data.stock;
          }
          break;
        case 5:
          if (order == 1) {
            rule2 = current->next->data.tExpired < newnode->data.tExpired;
          } else {
            rule2 = current->next->data.tExpired > newnode->data.tExpired;
          }
          break;
      }
