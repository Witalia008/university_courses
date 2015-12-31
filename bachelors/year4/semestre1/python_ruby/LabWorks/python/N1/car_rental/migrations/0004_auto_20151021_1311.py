# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0003_order_returned'),
    ]

    operations = [
        migrations.AlterField(
            model_name='order',
            name='rej_reason',
            field=models.TextField(blank=True, null=True),
        ),
    ]
