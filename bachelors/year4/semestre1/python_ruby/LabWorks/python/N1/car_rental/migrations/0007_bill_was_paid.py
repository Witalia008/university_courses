# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0006_remove_bill_price'),
    ]

    operations = [
        migrations.AddField(
            model_name='bill',
            name='was_paid',
            field=models.BooleanField(default=False),
        ),
    ]
