# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0007_bill_was_paid'),
    ]

    operations = [
        migrations.AlterField(
            model_name='bill',
            name='add_price_reason',
            field=models.TextField(blank=True),
        ),
    ]
